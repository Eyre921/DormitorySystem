#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

class Database
{
private:
    sqlite3 *db; // 数据库连接

public:
    // 构造函数，打开数据库
    Database(const string &dbPath);

    // 析构函数，关闭数据库
    ~Database();

    // 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
    bool execute(const string &sql);


    // 使用 sqlite3 命令行工具执行查询并格式化输出
    bool Query(const string &sql);
};

#endif // DATABASE_H
