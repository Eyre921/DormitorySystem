#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <map>
#include "User.h"
#include <sqlite3.h>

class UserManager
{
private:
    sqlite3 *db; // SQLite数据库连接
public:
    UserManager(); // 构造函数，初始化数据库
    ~UserManager(); // 析构函数，关闭数据库连接

    bool registerStudent(const std::string &studentID, const std::string &password,
                         const std::string &name, const std::string &gender, const std::string &contactInfo);

    bool isUserExists(const std::string &userID);

    User *loginUser(const std::string &userID, const std::string &password);

    void loadUsers(); // 可以根据需要实现加载用户
    void saveUsers(); // 可以根据需要实现保存用户
};

#endif // USERMANAGER_H
