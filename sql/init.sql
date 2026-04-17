create database if  not exists user_audit_system;
use user_audit_system;
drop table if not exists logs;
drop table if not exists users;
create table users(
    id int primary key auto_increment,
    username varchar(50) not null unique,
    password varchar(100) not null,
    role varchar(20)not null default 'user',
    created_at datetime default current_timestamp
);
create table logs(
    id int primary key auto_increment,
    username varchar(50) not null,
    action varchar(50) not null,
    detail varchar(250),
    created_at datetime default current_timestamp
);



