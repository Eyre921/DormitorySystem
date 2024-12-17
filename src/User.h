#ifndef USER_H
#define USER_H

#include <string>
#include <sqlite3.h>

class User
{
private:
    std::string userID; // 用户ID（学号或用户名）
    std::string name; // 姓名
    std::string password; // 密码
    std::string contactInfo; // 联系方式
    bool isAdmin; // 是否为管理员
    sqlite3 *db; // SQLite数据库连接

public:
    // 构造函数
    User(std::string userID, std::string name, std::string password, std::string contactInfo, bool isAdmin);

    // 析构函数
    ~User();

    // 打开数据库
    bool openDatabase(const std::string &dbPath);

    // 关闭数据库
    void closeDatabase();

    // 创建用户表
    bool createTable();

    // 插入用户
    bool insertUser();

    // 获取用户ID
    std::string getUserID() const;

    // 获取用户名
    std::string getName() const;

    // 检查密码是否正确
    bool checkPassword(const std::string &password) const;

    // 获取是否为管理员
    bool getIsAdmin() const;

    // 设置联系方式
    void setContactInfo(const std::string &contactInfo);

    // 获取联系方式
    std::string getContactInfo() const;
};

#endif // USER_H
