# 用户审计系统 (User Audit System)

这是一个基于 C++ 和 MySQL 的用户审计系统，用于管理用户账户并记录用户操作日志。

## 项目结构

- `src/`: 源代码文件
  - `main.cpp`: 主程序入口
  - `test_mysql.cpp`: MySQL 连接测试程序
- `sql/`: 数据库初始化脚本
  - `init.sql`: 创建数据库和表的 SQL 脚本
- `bin/`: 编译后的可执行文件
- `config/`: 配置文件
- `headFile/`: 头文件
- `myLog/`: 日志文件
- `temFile/`: 临时文件

## 数据库结构

- **users 表**: 存储用户信息
  - id: 用户ID (主键，自增)
  - username: 用户名 (唯一)
  - password: 密码
  - role: 角色 (默认 'user')
  - created_at: 创建时间

- **logs 表**: 存储操作日志
  - id: 日志ID (主键，自增)
  - username: 操作用户名
  - action: 操作类型
  - detail: 操作详情
  - created_at: 操作时间

## 构建和运行

### 依赖项

- CMake
- MySQL 开发库 (libmysqlclient-dev)
- C++ 编译器 (g++)

### 构建步骤

1. 安装依赖：
   ```bash
   sudo apt update
   sudo apt install cmake libmysqlclient-dev g++
   ```

2. 克隆或进入项目目录：
   ```bash
   cd /path/to/user_audit_system
   ```

3. 创建构建目录并编译：
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. 可执行文件将在 `bin/` 目录下生成：
   - `UserAuditSystem`: 主程序
   - `test_mysql`: MySQL 测试程序

### 数据库设置

1. 安装并启动 MySQL 服务：
   ```bash
   sudo apt install mysql-server
   sudo systemctl start mysql
   ```

2. 创建数据库用户和数据库：
   ```bash
   mysql -u root -p
   CREATE USER 'Daixusheng'@'localhost' IDENTIFIED BY '123456';
   CREATE DATABASE user_audit_system;
   GRANT ALL PRIVILEGES ON user_audit_system.* TO 'Daixusheng'@'localhost';
   FLUSH PRIVILEGES;
   EXIT;
   ```

3. 初始化数据库：
   ```bash
   mysql -u Daixusheng -p user_audit_system < sql/init.sql
   ```

### 运行程序

1. 运行主程序：
   ```bash
   cd bin
   ./UserAuditSystem
   ```

2. 运行 MySQL 测试：
   ```bash
   ./test_mysql
   ```
   然后输入用户名进行查询。

## 功能特性

- 用户管理：添加、查询用户
- 操作日志记录：记录用户登录、查询、更新等操作
- MySQL 数据库集成
- 简单的命令行界面

## 注意事项

- 密码存储为明文，生产环境建议使用哈希加密
- SQL 查询存在注入风险，建议使用预处理语句
- 确保 MySQL 服务运行并配置正确

## 贡献

欢迎提交 Issue 和 Pull Request！

## 许可证

MIT License