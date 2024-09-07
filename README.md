# Project-ws-server
A server program based on libwebsockets, the function is unknown, write functions based on feeling

本项目旨在:
- 通过libwebsockets库实现一个简单的服务器程序
- 实践设计模式
- 实践...

## 目录结构
- `3rdparty` :存放第三方库
- `src` :存放源代码

## 项目依赖
如无特殊说明，项目依赖都以 submodule 的形式引入

## 一键编译

直接运行 `build.sh` 脚本进行编译。

```bash
./build.sh
```

## Commit 规范
> [https://fe-notes.yunyoujun.cn/common/dev/#commit-message](https://fe-notes.yunyoujun.cn/common/dev/#commit-message)

- **build** ：对构建系统或者外部依赖项进行了修改
- **ci** ：对CI配置文件或脚本进行了修改
- **docs** ：对文档进行了修改
- **feat** ：增加新的特征
- **fix** ：修复bug
- **pref** ：提高性能的代码更改
- **refactor** ：既不是修复bug也不是添加特征的代码重构
- **style** ：不影响代码含义的修改，比如空格、格式化、缺失的分号等
- **test** ：增加确实的测试或者矫正已存在的测试
