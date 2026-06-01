# project

这个仓库是 Linux/C/C++ 学习项目集合，包含用户审计系统、简易 Shell、模拟 stdio、条件变量/线程池练习和 UDP Echo 示例。

## 目录内容

| 目录 | 内容 | 说明 |
| --- | --- | --- |
| `src/` | 用户审计系统 C++ 源码 | `main.cpp` 是主程序入口，`test_mysql.cpp` 是 MySQL 查询测试程序 |
| `sql/` | 数据库脚本 | `init.sql` 创建 `user_audit_system` 数据库表 |
| `myshell/` | 简易 Shell | 支持命令执行、`cd`、`echo $?`、`env` 和基础重定向 |
| `mystdio/` | 模拟 stdio | 用 `open/write/close` 实现简单文件写入缓冲 |
| `pthread_cond/` | 条件变量练习 | 从生产者消费者模型扩展到简单任务队列 |
| `threadpool/` | C++ 线程池 | 基于 `pthread`、任务队列和条件变量实现 |
| `echoserver/` | UDP Echo | 包含 UDP 服务端和客户端 |

## 构建说明

用户审计系统使用根目录 `CMakeLists.txt`：

```bash
mkdir -p build
cd build
cmake ..
make
```

其他小项目一般进入对应目录后执行：

```bash
make
```

生成的可执行文件、构建目录、日志和本地编辑器配置已加入 `.gitignore`，不建议提交到 GitHub。

## 当前整理原则

- 保留源码、SQL、Makefile、CMakeLists 和说明文档。
- 删除可重新生成的二进制文件。
- 每个小项目目录都补充独立 `README.md`，方便以后单独查看。
