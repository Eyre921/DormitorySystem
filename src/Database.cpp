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
    //sqlite3_stmt *stmt;

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
        return false;
    } else
    {
        cerr << "执行查询失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_finalize(stmt); // 释放 SQL 语句
    return true;
}

bool Database::QueryExists(const std::string &sql)
{
    // sqlite3_stmt *stmt;

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
        return true;
    } else if (result == SQLITE_DONE)
    {
        return false;
    } else
    {
        cerr << "执行查询失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_finalize(stmt); // 释放 SQL 语句
    return true;
}

int Database::getDormitoryIDByName(const string &dormitoryName)
{
    //sqlite3_stmt *stmt;
    string sql = "SELECT dormitoryID FROM dormitories WHERE name = ?";

    // 准备 SQL 查询语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return -1; // 返回无效ID
    }

    // 绑定参数（宿舍楼名称）
    sqlite3_bind_text(stmt, 1, dormitoryName.c_str(), -1, SQLITE_STATIC);

    // 执行查询并获取结果
    int dormitoryID = -1; // 默认为 -1，表示未找到
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        dormitoryID = sqlite3_column_int(stmt, 0); // 获取查询结果中的 dormitoryID
    }

    // 清理
    sqlite3_finalize(stmt);

    return dormitoryID;
}

bool Database::hasStudentsInDormitoryRooms(const string &checkRoomsSql)
{
    //sqlite3_stmt *stmt;
    int studentCount = 0;

    // 执行 SQL 查询，检查是否有学生入住
    if (sqlite3_prepare_v2(db, checkRoomsSql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // 执行查询并获取结果
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        studentCount++;
    }

    // 如果 studentCount > 0，表示有学生入住
    sqlite3_finalize(stmt);
    return studentCount > 0;
}

string Database::getQueryResult(int columnIndex)
{
    const char *text = (const char *) sqlite3_column_text(stmt, columnIndex);
    return text ? text : ""; // 如果没有数据则返回空字符串
}

void Database::updateRoomStatus()
{
    // 1. 统计每个房间的学生数
    string query = "SELECT r.roomID, COUNT(sr.studentID) AS studentCount "
            "FROM rooms r "
            "LEFT JOIN student_rooms sr ON r.roomID = sr.roomID "
            "GROUP BY r.roomID;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "Failed to prepare room status query: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // 2. 逐行处理统计结果，并更新房间的占用人数
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int roomID = sqlite3_column_int(stmt, 0); // 获取 roomID
        int studentCount = sqlite3_column_int(stmt, 1); // 获取学生数量

        // 3. 更新房间的占用人数
        string updateQuery = "UPDATE rooms SET occupied = ? WHERE roomID = ?;";

        if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, 0) != SQLITE_OK)
        {
            cerr << "Failed to prepare update query: " << sqlite3_errmsg(db) << endl;
            continue;
        }

        // 4. 绑定参数：occupied, roomID
        sqlite3_bind_int(stmt, 1, studentCount); // 绑定学生数量到 occupied 字段
        sqlite3_bind_int(stmt, 2, roomID); // 绑定 roomID 到 WHERE 条件

        // 执行更新操作
        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            cerr << "Failed to update room status: " << sqlite3_errmsg(db) << endl;
        }

        // 5. 重置语句，准备下一次使用
        sqlite3_reset(stmt);
    }

    // 6. 释放语句资源
    sqlite3_finalize(stmt);
}


