#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database
{
private:
    sqlite3 *db; // 数据库连接

public:
    // 构造函数，打开数据库
    Database(const std::string &dbPath);

    // 析构函数，关闭数据库
    ~Database();

    // 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
    bool execute(const std::string &sql);

    // 执行查询操作（SELECT），并输出带框线的表格结果
    bool executeQuery(const std::string &sql);

    // 使用 sqlite3 命令行工具执行查询并格式化输出
    bool Query(const std::string &sql);

    // 插入用户数据
    bool user_insert(const std::string &userID, const std::string &name, const std::string &gender,
                     const std::string &password, const std::string &contactInfo, int isCheckedIn, int isAdmin);
};

#endif // DATABASE_H
