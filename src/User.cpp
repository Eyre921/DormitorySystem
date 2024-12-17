#include "User.h"
#include <iostream>

using namespace std;

// 构造函数，初始化成员变量并打开数据库
User::User(string userID, string name, string password, string contactInfo, bool isAdmin)
    : userID(userID), name(name), password(password), contactInfo(contactInfo), isAdmin(isAdmin), db(nullptr)
{
    openDatabase("../data/dormitory.db");
    createTable(); // 初始化数据库时创建用户表
}

// 析构函数，关闭数据库连接
User::~User()
{
    closeDatabase();
}

// 打开数据库
bool User::openDatabase(const string &dbPath)
{
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc)
    {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    cout << "成功打开数据库!" << endl;
    return true;
}

// 关闭数据库
void User::closeDatabase()
{
    if (db)
    {
        sqlite3_close(db);
        cout << "数据库已关闭!" << endl;
    }
}

// 创建用户表
bool User::createTable()
{
    const string createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            userID TEXT UNIQUE NOT NULL,
            name TEXT NOT NULL,
            password TEXT NOT NULL,
            contactInfo TEXT,
            isAdmin INTEGER NOT NULL
        );
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        cerr << "创建表失败: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    cout << "用户表已创建或已存在!" << endl;
    return true;
}

// 插入用户数据
bool User::insertUser()
{
    const string insertSQL = R"(
        INSERT INTO users (userID, name, password, contactInfo, isAdmin)
        VALUES (?, ?, ?, ?, ?);
    )";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, contactInfo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, isAdmin ? 1 : 0);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "插入数据失败: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    cout << "用户插入成功!" << endl;
    sqlite3_finalize(stmt);
    return true;
}

// 获取用户ID
string User::getUserID() const
{
    return userID;
}

// 获取用户名
string User::getName() const
{
    return name;
}

// 检查密码是否正确
bool User::checkPassword(const string &inputPassword) const
{
    return password == inputPassword;
}

// 获取是否为管理员
bool User::getIsAdmin() const
{
    return isAdmin;
}

// 设置联系方式
void User::setContactInfo(const string &newContactInfo)
{
    contactInfo = newContactInfo;
}

// 获取联系方式
string User::getContactInfo() const
{
    return contactInfo;
}
