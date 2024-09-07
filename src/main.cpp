#include <libwebsockets.h>
#include <signal.h>
#include <string.h>

static int exit_sig = 0;
#define MAX_PAYLOAD_SIZE 10 * 1024

void dosomething()
{
    lwsl_debug("dosomething\n");
}

void sighdl(int sig)
{
    lwsl_notice("%d traped", sig);
    exit_sig = 1;
}

/**
 * 会话上下文对象，结构根据需要自定义
 */
struct session_data
{
    int msg_count;
    unsigned char buf[LWS_PRE + MAX_PAYLOAD_SIZE];
    int len;
    bool bin;
    bool fin;
};

static int protocol_my_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    struct session_data *data = (struct session_data *)user;
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
        lwsl_debug("Client connect!\n");
        data->len = 0;
        break;

    case LWS_CALLBACK_RECEIVE:
        lwsl_debug("LWS_CALLBACK_RECEIVE\n");
        data->fin = lws_is_final_fragment(wsi);
        data->bin = lws_frame_is_binary(wsi);
        lws_rx_flow_control(wsi, 0);

        memcpy(&data->buf[LWS_PRE + data->len], in, len);
        data->len += len;

        if (data->fin)
        {
            dosomething();
            lwsl_debug("Received: %s\n", &data->buf[LWS_PRE]);
            lws_callback_on_writable(wsi);
        }
        break;
    case LWS_CALLBACK_SERVER_WRITEABLE:
        lws_write(wsi, &data->buf[LWS_PRE], data->len, LWS_WRITE_TEXT);
        data->len = 0;
        memset(data->buf, 0, sizeof(data->buf));
        lws_rx_flow_control(wsi, 1);
        break;
    }
    return 0;
}

/**
 * 支持的WebSocket子协议数组
 * 子协议即JavaScript客户端WebSocket(url, protocols)第2参数数组的元素
 * 你需要为每种协议提供回调函数
 */
struct lws_protocols protocols[] = {
    {
        // 协议名称，协议回调，接收缓冲区大小
        "ws",
        protocol_my_callback,
        sizeof(struct session_data),
        MAX_PAYLOAD_SIZE,
    },
    {
        NULL, NULL, 0 // 最后一个元素固定为此格式
    }};

int main(int argc, char **argv)
{
    signal(SIGTERM, sighdl);

    struct lws_context_creation_info ctx_info = {0};
    ctx_info.port = 8000;
    // ctx_info.iface = NULL; // 在所有网络接口上监听
    ctx_info.protocols = protocols;
    ctx_info.gid = -1;
    ctx_info.uid = -1;
    ctx_info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;

    // ctx_info.ssl_ca_filepath = "../ca/ca-cert.pem";
    // ctx_info.ssl_cert_filepath = "./server-cert.pem";
    // ctx_info.ssl_private_key_filepath = "./server-key.pem";
    // ctx_info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    // ctx_info.options |= LWS_SERVER_OPTION_REQUIRE_VALID_OPENSSL_CLIENT_CERT;

    struct lws_context *context = lws_create_context(&ctx_info);
    while (!exit_sig)
    {
        lws_service(context, 1000);
    }
    lws_context_destroy(context);

    return 0;
}