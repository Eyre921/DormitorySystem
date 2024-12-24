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

    if (db.QueryExists(sql))
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

bool UserManager::queryExists(string &SQL)
{
    return db.QueryExists(SQL);
}

bool UserManager::dormitoryExistsByName(const string &dormitoryName)
{
    // 模拟查询语句
    string sql = "SELECT * FROM dormitories WHERE name = '" + dormitoryName + "';";

    // 调用查询函数来检查数据库中是否已有该宿舍楼名称
    if (db.QueryExists(sql))
    {
        return true; // 如果返回 true，表示该宿舍楼名称已存在
    } else
    {
        return false; // 如果没有找到，表示该宿舍楼名称不存在
    }
}

bool UserManager::studentExistsByID(const string &ID)
{
    // 模拟查询语句
    string sql = "SELECT * FROM users WHERE userID = '" + ID + "';";

    if (db.QueryExists(sql))
    {
        return true;
    } else
    {
        return false;
    }
}

int UserManager::getDormitoryIDByName(const string &dormitoryName)
{
    return db.getDormitoryIDByName(dormitoryName);
}

bool UserManager::hasStudentsInDormitoryRooms(const string &checkRoomsSql)
{
    return db.hasStudentsInDormitoryRooms(checkRoomsSql);
}

bool UserManager::UserPasswordChange(const string &userID)
{
    cout << "请输入新密码:";
    string newPassword;
    cin >> newPassword;
    // 构造插入语句
    string sql = "UPDATE users SET password = " + newPassword + " WHERE userID = " + userID + ";";
    // 尝试执行插入操作
    if (db.execute(sql))
    {
        cout << "密码修改成功！\n";
        return true;
    } else
    {
        cout << "密码修改失败……\n";
        return false; // 插入失败
    }
}
