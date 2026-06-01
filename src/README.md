# 用户审计系统源码

这个目录保存用户审计系统的 C++ 源码。

## 文件说明

- `main.cpp`：主程序入口，目前输出用户审计系统提示信息。
- `test_mysql.cpp`：MySQL 连接和用户查询测试程序。

## 依赖

- C++17 编译器
- MySQL C API 开发库，例如 Ubuntu/Debian 下的 `libmysqlclient-dev`

## 构建

在仓库根目录执行：

```bash
mkdir -p build
cd build
cmake ..
make
```

会生成：

- `UserAuditSystem`
- `test_mysql`

## 注意

`test_mysql.cpp` 当前直接拼接 SQL 字符串，存在 SQL 注入风险。后续可以改成 MySQL 预处理语句。
