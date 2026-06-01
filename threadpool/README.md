# threadpool

一个基于 C++ 和 `pthread` 的简单线程池实现。

## 功能

- `Task` 封装任务函数和参数。
- `WaitQueue` 使用队列、互斥锁和条件变量管理任务。
- `ThreadPool` 创建固定数量工作线程。
- 支持任务提交和停止线程池。

## 文件说明

- `threadpool.hpp`：线程池主要实现。
- `threadpool.cpp`：当前为空文件，预留给后续拆分实现。
- `main.cpp`：线程池测试程序。
- `Makefile`：编译脚本。

## 构建和运行

```bash
make
./threadpool
```

清理生成文件：

```bash
make clean
```
