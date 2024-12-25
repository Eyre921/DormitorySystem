#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

class Database
{
public:
    sqlite3 *db; // 数据库连接
    sqlite3_stmt *stmt;

    // 构造函数，打开数据库
    Database(const string &dbPath);

    // 析构函数，关闭数据库
    ~Database();

    // 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
    bool execute(const string &sql);

    bool Query(const string &sql);

    bool QueryExists(const std::string &sql);

    int getDormitoryIDByName(const string &dormitoryName);

    bool hasStudentsInDormitoryRooms(const string &checkRoomsSql);


    bool updateRoomStatus();

    string getQueryResult(int columnIndex);
};

#endif // DATABASE_H
