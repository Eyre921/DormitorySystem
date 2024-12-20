#include "UserManager.h"
#include <iostream>

using namespace std;

// 构造函数，自动连接数据库
UserManager::UserManager() : db("../data/dormitory.db")
{
    // 直接在这里指定数据库路径
    // 在这里，可以进行数据库的初始化（例如创建表等操作）
    // if (!db.execute(
    //     "CREATE TABLE IF NOT EXISTS users (userID TEXT PRIMARY KEY, name TEXT, gender TEXT, password TEXT, contactInfo TEXT, isCheckedIn INTEGER DEFAULT 0, isAdmin INTEGER DEFAULT 0);"))
    // {
    //     cout << "数据库创建失败！\n";
    //     exit(1); // 如果数据库创建失败，退出程序
    // }
}

// 用户登录
bool UserManager::loginUser(const string &userID, const string &password, const string &isAdmin)
{
    string sql = "SELECT * FROM users WHERE userID = '" + userID + "' AND password = '" + password + "' AND isAdmin = '"
                 + isAdmin + "';";

    if (db.Query(sql))
    {
        cout << "登录成功！";
        return true; // 登录成功
    }
    cout << "登录失败！";
    return false; // 登录失败
}

// 用户注册
bool UserManager::registerUser(const string &userID, const string &password, const string &name, const string &gender,
                               const string &contactInfo, bool isCheckedIn, bool isAdmin)
{
    // 构造插入语句
    string sql = "INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) "
                 "VALUES ('" + userID + "', '" + name + "', '" + gender + "', '" + password + "', '" + contactInfo +
                 "', " + to_string(isCheckedIn) + ", " + to_string(isAdmin) + ");";

    // 尝试执行插入操作
    if (db.execute(sql))
    {
        cout << "用户注册成功！\n";
        return true;
    } else
    {
        cout << "用户注册失败，可能是账号已存在。\n";
        return false; // 插入失败
    }
}

// 获取所有用户
void UserManager::getAllUsers()
{
    db.Query("SELECT * FROM users;");
}


void UserManager::Query(string &SQL)
{
    db.Query(SQL);
}

void UserManager::execute(string &SQL)
{
    db.execute(SQL);
}
