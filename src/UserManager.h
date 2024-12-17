// UserManager.h

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class UserManager {
public:
    UserManager(const std::string& dbFile);   // 构造函数
    ~UserManager();                           // 析构函数

    // 用户管理操作
    bool createUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);

private:
    sqlite3* db;                             // SQLite数据库连接
    std::string dbFile;                      // 数据库文件路径

    // 创建用户表
    bool createTableIfNotExists();
};

#endif // USERMANAGER_H
