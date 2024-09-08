#ifndef H_SINGLETON
#define H_SINGLETON

#include <mutex>
#include <memory>
#include <utility>

/**
 * @brief 单例模式模板
 * 
 * tips: 
 * 1. 就地实现时，可以不加 inline 关键字
 */
template <typename T>
class Singleton {
public:
    template <typename... Args>
    static T& Instance(Args&&... args) {
        std::call_once(initFlag, [&](Args&&... args) {
            instance.reset(new T(std::forward<Args>(args)...));
        }, std::forward<Args>(args)...);
        return *instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    static std::unique_ptr<T> instance;
    static std::once_flag initFlag;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;

template <typename T>
std::once_flag Singleton<T>::initFlag;

#endif // H_SINGLETON
