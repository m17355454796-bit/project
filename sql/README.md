# SQL 初始化脚本

这个目录保存用户审计系统的数据库脚本。

## 文件说明

- `init.sql`：创建 `user_audit_system` 数据库，并初始化 `users` 和 `logs` 表。

## 使用方式

```bash
mysql -u root -p < sql/init.sql
```

或者先进入 MySQL 后手动执行脚本内容。

## 表结构

- `users`：保存用户 ID、用户名、密码、角色和创建时间。
- `logs`：保存用户操作日志，包括用户名、操作类型、详情和创建时间。
