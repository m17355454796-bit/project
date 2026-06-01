# echoserver

一个 UDP Echo 示例项目，包含服务端和客户端。

## 功能

- `UdpEchoServer`：绑定指定 IP 和端口，接收 UDP 数据并原样返回。
- `UdpEchoClient`：向服务端发送用户输入内容，并打印服务端返回的数据。

## 文件说明

- `UdpEchoServer.hpp`：UDP 服务端类实现。
- `UdpEchoServer.cc`：服务端入口。
- `UdpEchoClient.cc`：客户端入口。
- `Makefile`：编译服务端和客户端。

## 构建

```bash
make
```

## 运行示例

先启动服务端：

```bash
./UdpEchoServer 127.0.0.1 8080
```

再启动客户端：

```bash
./UdpEchoClient 127.0.0.1 8080
```

清理生成文件：

```bash
make clean
```
