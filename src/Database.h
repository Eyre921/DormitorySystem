#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Database
{
public:
    sqlite3 *db; // 数据库连接
    sqlite3_stmt *stmt;

    // 构造函数，打开数据库
    explicit Database(const string &dbPath): stmt(nullptr)
    {
        if (sqlite3_open(dbPath.c_str(), &db))
        {
            cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
            db = nullptr;
        } else
        {
            //cout << "数据库连接成功！" << endl;
        }
    }

    // 析构函数，关闭数据库
    ~Database()
    {
        if (db)
        {
            sqlite3_close(db);
            cout << "数据库已关闭！" << endl;
        }
    }

    // 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
    bool execute(const string &sql) const;

    bool query(const string &sql);

    bool queryExists(const std::string &sql);

    //int getDormitoryIDByName(const string &dormitoryName);

    bool queryWithParams(const string &query, const std::vector<std::string> &params);

    void executeWithParams(const std::string &sql, const std::vector<std::string> &params);

    bool updateRoomStatus() const;

    string getQueryResult(int columnIndex);
};

#endif // DATABASE_H
