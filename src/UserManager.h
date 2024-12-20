#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "Database.h"

#include <string>
#include <vector>

class UserManager
{
private:
    Database db; // 数据库对象，自动连接

public:
    // 构造函数，自动连接数据库
    UserManager();

    // 用户登录
    bool loginUser(const string &userID, const string &password, const string &isAdmin);

    // 用户注册
    bool registerUser(const std::string &userID, const std::string &password, const std::string &name,
                      const std::string &gender, const std::string &contactInfo, bool isCheckedIn, bool isAdmin);

    void UserManager::execute(string &SQL);

    // 获取所有用户
    void getAllUsers();

    void UserManager::Query(string &SQL);

    // 检查用户是否存在
};

#endif // USERMANAGER_H
