#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "Database.h"


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

    void execute(const string &SQL);

    // 获取所有用户
    void getAllUsers();

    void Query(const string &SQL);

    bool queryExists(const string &SQL);

    bool QueryExists(const std::string &sql);

    bool dormitoryExistsByName(const string &dormitoryName);

    int getDormitoryIDByName(const string &dormitoryName);

    bool hasStudentsInDormitoryRooms(const string &checkRoomsSql);

    bool studentExistsByID(const string &ID);

    bool UserPasswordChange(const string &userID);

    void arrangeAccommodation(const string &studentID);

    void QuickArrangeAccommodation(const string &studentID, const string &dormitoryName, const string &roomChoice);

    void SelectValidRoom(const string &studentID, string &dormitoryName, string &roomChoice);

    void arrangeCheckOut(const string &studentID);

    void requestRoomChange(const string &studentID);

    void QuickArrangeCheckOut(const string &studentName, const string &studentID, const string &dormitoryName,
                              const string &roomNumber, const string
                              &note);

    bool IsStudentCheckedIn(const string &studentID);

    bool IDExists(const string &studentID);

    string Get_ID();

    void checkUserInfo(const string &userID);

    void deleteUser(const string &userID);

    void checkUserInfoALL();

    void checkUserInfoByName(const string &userName);

    // 检查用户是否存在
};

#endif // USERMANAGER_H
