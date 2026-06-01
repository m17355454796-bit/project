# mystdio

一个用系统调用模拟 C 标准 IO 写缓冲的练习项目。

## 功能

- `myFopen`：根据 `r/w/a` 模式打开文件。
- `myFwrite`：写入用户缓冲区数据到自定义缓冲区。
- `myFflush`：把自定义缓冲区写入文件描述符。
- `myFclose`：刷新缓冲并关闭文件。

## 文件说明

- `mystdio.c`：自定义文件接口实现。
- `mystdio.h`：`myFile` 结构体和函数声明。
- `main.c`：测试程序，向 `big.txt` 写入数据。
- `Makefile`：编译脚本。

## 构建和运行

```bash
make
./main
```

清理生成文件：

```bash
make clean
```

`big.txt`、`log.txt` 和可执行文件属于运行产物，不建议提交。
