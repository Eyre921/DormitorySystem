#include "Database.h"
#include <cstdlib>  // for system()
#include <vector>
using namespace std;
/*
以下是对当前文件的代码找茬：
对提供的Database.cpp源代码进行分析，可以发现以下几类问题：

1. 安全问题
SQL注入风险：在execute函数中直接执行传入的SQL字符串，没有对输入进行任何验证或清理，这可能导致SQL注入攻击。
未初始化的指针：在多个函数中使用了未初始化的sqlite3_stmt *stmt指针（例如query、queryExists、queryWithParams等函数），这可能导致未定义行为。
2. 性能问题
重复的SQL准备和执行：在多个函数中重复执行类似的SQL准备和执行逻辑，这可能导致不必要的性能开销。可以考虑将这些逻辑封装成一个通用的函数以提高代码的可重用性和性能。
不必要的字符串转换：在queryWithParams和executeWithParams函数中，将std::string转换为C风格字符串(c_str())可能会带来不必要的性能开销，尤其是在大量数据处理时。
3. 代码质量问题
未使用的变量：在queryExists函数中，columnName和columnValue被获取但未使用，这可能是代码冗余。
不一致的错误处理：在不同的函数中，错误处理方式不一致。有些函数使用cerr输出错误信息，而有些函数使用cout。建议统一错误处理方式。
缺少资源释放：在query、queryExists、queryWithParams和executeWithParams函数中，如果sqlite3_prepare_v2失败，stmt指针未被释放。虽然这些情况下stmt未被赋值，但最好确保所有路径都正确地释放资源。
硬编码的SQL语句：在updateRoomStatus函数中，SQL语句是硬编码的，这不利于维护和修改。建议将SQL语句外部化，例如使用配置文件或常量。
4. 潜在的逻辑缺陷
sqlite3_finalize调用位置不当：在query和queryExists函数中，sqlite3_finalize(stmt)的调用位置在返回语句之后，这将导致它永远不会被执行。应将其放在合适的位置以确保资源被正确释放。
错误的返回逻辑：在query函数中，如果查询成功但没有返回任何行（即result == SQLITE_DONE），函数返回false，这可能与预期不符。应根据具体业务逻辑调整返回值。
5. 其他建议
使用智能指针：考虑使用智能指针（如std::unique_ptr）来管理sqlite3_stmt资源，以避免手动管理内存和减少内存泄漏的风险。
增加日志记录：在关键操作（如SQL执行、错误处理）处增加日志记录，有助于后期的调试和问题排查。
代码注释和文档：增加代码注释和文档，特别是对于复杂的逻辑部分，以便其他开发者理解和维护代码。
以上是对Database.cpp源代码的详细分析和建议，希望对改进代码质量和安全性有所帮助。
 */
// 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
// 执行SQL语句
bool Database::execute(const string &sql) const
{
    // 检查数据库是否已连接
    if (db == nullptr)
    {
        cerr << "数据库未连接！" << endl;
        return false; // 如果数据库未连接，返回 false
    }

    char *errMsg = nullptr; // 用于存储错误信息
    // 执行SQL语句，如果执行失败，则返回 false，并输出错误信息
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cerr << "SQL 执行失败: " << errMsg << endl; // 输出错误信息
        sqlite3_free(errMsg); // 释放错误信息
        return false; // 返回执行失败
    }
    return true; // 执行成功，返回 true
}


// 查询并打印
// 执行查询操作并处理查询结果
bool Database::query(const std::string &sql)
{
    // 声明 SQLite 语句指针
    sqlite3_stmt *stmt;

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        // 如果 SQL 编译失败，输出错误信息并返回 false
        cerr << "SQL 语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // 执行查询操作
    int result = sqlite3_step(stmt);

    // 处理查询结果
    if (result == SQLITE_ROW) // 如果查询到一行数据
    {
        // 获取列数
        int columnCount = sqlite3_column_count(stmt);

        // 打印查询结果
        cout << "查询结果:\n";
        while (result == SQLITE_ROW) // 如果还有下一行数据
        {
            // 遍历每一列
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
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return true; // 返回查询成功
    } else if (result == SQLITE_DONE) // 如果查询没有返回结果（如空查询）
    {
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return false; // 返回 false，表示没有查询结果
    } else // 执行查询失败
    {
        cerr << "执行查询失败: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return false; // 返回 false，表示查询执行失败
    }
}

// 查询存在性
bool Database::queryExists(const std::string &sql)
{
    // sqlite3_stmt *stmt;

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "SQL 语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false; // 如果 SQL 编译失败，输出错误并返回 false
    }

    // 执行查询操作
    int result = sqlite3_step(stmt);

    // 处理查询结果
    if (result == SQLITE_ROW) // 如果查询返回了一行数据
    {
        // 获取列数
        int columnCount = sqlite3_column_count(stmt);

        // 只需要判断是否存在结果，不需要输出具体的查询数据
        while (result == SQLITE_ROW)
        {
            for (int i = 0; i < columnCount; ++i)
            {
                // 获取列名和列值，但这里并不需要实际输出，只判断是否存在数据
                const char *columnName = sqlite3_column_name(stmt, i); // 获取列名
                const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)); // 获取列值
            }
            result = sqlite3_step(stmt); // 继续执行下一行
        }
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return true; // 如果查询结果存在，则返回 true
    } else if (result == SQLITE_DONE) // 如果没有查询到数据（没有行数据）
    {
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return false; // 返回 false，表示没有找到符合条件的数据
    } else
    {
        cerr << "执行查询失败: " << sqlite3_errmsg(db) << endl; // 如果查询执行失败，输出错误信息
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return false; // 返回 false，表示查询执行失败
    }
}


// 带参查询
// 使用参数执行查询
bool Database::queryWithParams(const string &query, const std::vector<std::string> &params)
{
    // 准备查询语句
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false; // 如果 SQL 语句编译失败，输出错误信息并返回 false
    }

    // 绑定参数
    for (size_t i = 0; i < params.size(); ++i)
    {
        // 将每个参数绑定到预处理语句中，i + 1 是因为 SQL 语句中的参数从 1 开始
        if (sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
        {
            cout << "Failed to bind params: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt); // 如果绑定参数失败，释放语句并返回 false
            return false;
        }
    }

    // 执行查询
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        // 如果查询没有返回行数据，表示没有匹配的结果
        sqlite3_finalize(stmt); // 释放 SQL 语句
        return false;
    }

    // 查询成功，返回 true
    return true;
}


// 带参执行
// 执行带参数的 SQL 语句
void Database::executeWithParams(const std::string &sql, const std::vector<std::string> &params)
{
    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        // 如果 SQL 语句编译失败，输出错误信息并返回
        cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // 绑定参数
    for (size_t i = 0; i < params.size(); ++i)
    {
        // 将每个参数绑定到 SQL 语句中的对应位置，i + 1 是因为 SQL 中的参数从 1 开始编号
        if (sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
        {
            // 如果参数绑定失败，输出错误信息并释放资源
            cout << "Failed to bind params: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt); // 释放语句资源
            return;
        }
    }

    // 执行 SQL 语句
    if (sqlite3_step(stmt) != SQLITE_DONE) // 如果执行失败
    {
        cout << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    } else
    {
        // 如果执行成功，可以选择输出成功信息（这里注释掉）
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

    // 定义错误消息指针
    char *errMsg = nullptr;

    // 执行 SQL 语句，更新房间的占用人数
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    // 如果执行失败，输出错误信息并释放资源
    if (rc != SQLITE_OK)
    {
        // std::cerr << "更新房间状态失败: " << errMsg << std::endl; // 可取消注释输出错误信息
        sqlite3_free(errMsg); // 释放错误消息
        return false; // 返回 false，表示操作失败
    }

    // std::cout << "房间占用人数更新成功。" << std::endl; // 可取消注释输出成功信息
    return true; // 返回 true，表示操作成功
}







