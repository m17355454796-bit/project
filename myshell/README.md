# myshell

一个用 C 语言实现的简易 Shell 练习项目。

## 功能

- 显示类似 `user@host:path$` 的提示符。
- 解析并执行普通 Linux 命令。
- 内置支持 `cd`、`echo $?`、`env`、`exit`。
- 支持基础重定向：`>`、`>>`、`<`。

## 文件说明

- `main.c`：程序入口，调用 `Bash()`。
- `myshell.c`：Shell 主循环、命令解析、内置命令、重定向和子进程执行逻辑。
- `myshell.h`：公共头文件。
- `Makefile`：编译脚本。
- `myshell.md`：重定向功能学习记录。

## 构建和运行

```bash
make
./myshell
```

清理生成文件：

```bash
make clean
```
