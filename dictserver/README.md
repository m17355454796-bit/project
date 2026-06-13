# dictserver - UDP 字典服务器

一个基于 UDP 协议的英译中字典查询服务，包含服务端和客户端。

## 功能

- **UdpDictServer**：绑定指定 IP 和端口，接收客户端发送的英文单词，查询字典并返回对应的中文翻译。
- **UdpDictClient**：向服务端发送用户输入的英文单词，并打印服务端返回的翻译结果。

## 文件说明

| 文件 | 说明 |
|------|------|
| `UdpDictServer.hpp` | UDP 服务端类实现，包含 socket 创建、绑定、消息接收与发送 |
| `UdpDictServer.cc` | 服务端入口，初始化字典和服务器并启动 |
| `UdpDictClient.cc` | 客户端入口，循环接收用户输入并发送/接收 UDP 消息 |
| `dictionary.hpp` | 字典类实现，从文件加载词库并提供翻译功能 |
| `dict_words.txt` | 词库文件，每行格式：`英文 中文` |
| `Makefile` | 编译服务端和客户端 |

## 构建

```bash
make
```

## 运行示例

先启动服务端：

```bash
./UdpDictServer 127.0.0.1 8888
```

再启动客户端（新终端）：

```bash
./UdpDictClient 127.0.0.1 8888
```

客户端输入英文单词即可查询翻译：

```
请输入一段文字#apple
苹果
请输入一段文字#mouse
鼠标
```

清理生成文件：

```bash
make clean
```

## 依赖

- C++14 兼容的编译器（g++）
- Linux 环境（依赖 POSIX socket API）
