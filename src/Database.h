#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

// 数据库类，用于管理与SQLite数据库的连接
class Database {
public:
    Database(const std::string &db_name);  // 构造函数，打开数据库
    ~Database();  // 析构函数，关闭数据库

    sqlite3 *getConnection();  // 获取数据库连接

private:
    sqlite3 *db;  // 数据库连接
};

#endif // DATABASE_H
