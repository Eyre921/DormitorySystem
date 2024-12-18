#include "UserManager.h"
#include <iostream>
#include <sqlite3.h>

UserManager::UserManager()
{
    // 打开或创建数据库
    int rc = sqlite3_open("../data/dormitory.db", &db);
    if (rc)
    {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

UserManager::~UserManager()
{
    sqlite3_close(db); // 关闭数据库
}

// 注册学生
bool UserManager::registerStudent(const std::string &studentID, const std::string &password,
                                  const std::string &name, const std::string &gender, const std::string &contactInfo)
{
    if (isUserExists(studentID))
    {
        std::cout << "该学号已被注册！\n";
        return false; // 用户已存在
    }

    // SQL语句
    std::string sql = "INSERT INTO students (studentID, password, name, gender, contactInfo) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, studentID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, gender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, contactInfo.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "插入数据失败: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "学生注册成功！\n";
    return true;
}

// 检查用户是否已存在
bool UserManager::isUserExists(const std::string &userID)
{
    std::string sql = "SELECT COUNT(*) FROM students WHERE studentID = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        std::cerr << "查询失败: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count > 0; // 如果返回值大于0，表示用户存在
}

// 登录用户（可以扩展到管理员登录）
User *UserManager::loginUser(const std::string &userID, const std::string &password)
{
    std::string sql = "SELECT * FROM students WHERE studentID = ? AND password = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        std::cerr << "登录失败: 用户ID或密码错误！\n";
        sqlite3_finalize(stmt);
        return nullptr;
    }

    // 用户登录成功
    std::string name = (const char *) sqlite3_column_text(stmt, 2);
    bool isAdmin = sqlite3_column_int(stmt, 4); // 假设数据库有管理员字段
    User *user = new User(userID, name, password, "", isAdmin); // 创建用户对象（简化处理）
    sqlite3_finalize(stmt);

    return user;
}
