#include "Database.h"
#include <cstdlib>  // for system()
#include <vector>
using namespace std;

// 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
bool Database::execute(const string &sql) const
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

// 查询并打印
bool Database::query(const std::string &sql)
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

// 查询存在性
bool Database::queryExists(const std::string &sql)
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
        // 获取列数
        //int columnCount = sqlite3_column_count(stmt);

        // 打印查询结果

        while (result == SQLITE_ROW)
        {
            // for (int i = 0; i < columnCount; ++i)
            // {
            //     const char *columnName = sqlite3_column_name(stmt, i); // 获取列名
            //     const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)); // 获取列值
            // }
            // //cout << endl; // 打印一行数据后换行
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

// 带参查询
bool Database::queryWithParams(const string &query, const std::vector<std::string> &params)
{
    // 准备查询语句
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // 绑定参数
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
        {
            cout << "Failed to bind params: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return false;
        }
    }

    // 执行查询
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        //cerr << "No rows found" << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    return true;
}

// 带参执行
void Database::executeWithParams(const std::string &sql, const std::vector<std::string> &params)
{
    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // 绑定参数
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
        {
            cout << "Failed to bind params: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return;
        }
    }

    // 执行查询
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    } else
    {
        // cout << "Query executed successfully.\n";
    }

    // 释放语句资源
    sqlite3_finalize(stmt);
}

// 通过宿舍名获得ID
// int Database::getDormitoryIDByName(const string &dormitoryName)
// {
//     //sqlite3_stmt *stmt;
//     string sql = "SELECT dormitoryID FROM dormitories WHERE name = ?";
//
//     // 准备 SQL 查询语句
//     if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
//     {
//         cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
//         return -1; // 返回无效ID
//     }
//
//     // 绑定参数（宿舍楼名称）
//     sqlite3_bind_text(stmt, 1, dormitoryName.c_str(), -1, SQLITE_STATIC);
//
//     // 执行查询并获取结果
//     int dormitoryID = -1; // 默认为 -1，表示未找到
//     if (sqlite3_step(stmt) == SQLITE_ROW)
//     {
//         dormitoryID = sqlite3_column_int(stmt, 0); // 获取查询结果中的 dormitoryID
//     }
//
//     // 清理
//     sqlite3_finalize(stmt);
//
//     return dormitoryID;
// }

// bool Database::hasStudentsInDormitoryRooms(const string &checkRoomsSql)
// {
//     //sqlite3_stmt *stmt;
//     int studentCount = 0;
//
//     // 执行 SQL 查询，检查是否有学生入住
//     if (sqlite3_prepare_v2(db, checkRoomsSql.c_str(), -1, &stmt, 0) != SQLITE_OK)
//     {
//         cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
//         return false;
//     }
//
//     // 执行查询并获取结果
//     while (sqlite3_step(stmt) == SQLITE_ROW)
//     {
//         studentCount++;
//     }
//
//     // 如果 studentCount > 0，表示有学生入住
//     sqlite3_finalize(stmt);
//     return studentCount > 0;
// }

// 获取查询结果
string Database::getQueryResult(int columnIndex)
{
    const char *text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, columnIndex));
    return text ? text : ""; // 如果没有数据则返回空字符串
}

// 自动更新房间占用人数
bool Database::updateRoomStatus() const
{
    // SQL 语句：更新 rooms 表的 occupied 字段
    const char *sql = R"(
            UPDATE rooms
            SET occupied = (
                SELECT COUNT(*)
                FROM student_rooms
                WHERE student_rooms.roomID = rooms.roomID
            )
        )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        //std::cerr << "更新房间状态失败: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    //std::cout << "房间占用人数更新成功。" << std::endl;
    return true;
}






