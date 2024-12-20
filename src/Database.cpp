#include "Database.h"
#include <cstdlib>  // for system()
#include <vector>
using namespace std;

// 构造函数，打开数据库
Database::Database(const string &dbPath)
{
    if (sqlite3_open(dbPath.c_str(), &db))
    {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    } else
    {
        cout << "数据库连接成功！" << endl;
    }
}

// 析构函数，关闭数据库
Database::~Database()
{
    if (db)
    {
        sqlite3_close(db);
        cout << "数据库已关闭！" << endl;
    }
}

// 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
bool Database::execute(const string &sql)
{
    if (db == nullptr)
    {
        cerr << "数据库未连接！" << endl;
        return false;
    }

    char *errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cerr << "SQL 执行失败: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}


// 查询
bool Database::Query(const std::string &sql)
{
    sqlite3_stmt *stmt;

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "SQL 语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // 执行查询操作
    int result = sqlite3_step(stmt);

    // 处理查询结果
    if (result == SQLITE_ROW)
    {
        // 获取列数
        int columnCount = sqlite3_column_count(stmt);

        // 打印查询结果
        cout << "查询结果:\n";
        while (result == SQLITE_ROW)
        {
            for (int i = 0; i < columnCount; ++i)
            {
                const char *columnName = sqlite3_column_name(stmt, i); // 获取列名
                const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)); // 获取列值

                // 打印列名和对应的值
                cout << columnName << ": " << (columnValue ? columnValue : "NULL") << "  ";
            }
            cout << endl; // 打印一行数据后换行
            result = sqlite3_step(stmt); // 继续执行下一行
        }
        return true;
    } else if (result == SQLITE_DONE)
    {
        cout << "查询没有结果。\n"; // 查询没有结果
        return false;
    } else
    {
        cerr << "执行查询失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_finalize(stmt); // 释放 SQL 语句
    return true;
}

