#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "Database.h"
#include <set>
using namespace std;

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

    void QuickArrangeAccommodation(const string &studentID, const string &dormitoryName, const string &roomChoice,
                                   const string &note);

    void SelectValidRoom(const string &studentID, string &dormitoryName, string &roomChoice);

    void arrangeCheckOut(const string &studentID);

    void requestRoomChange(const string &studentID);

    void QuickArrangeCheckOut(const string &studentID, const string &note);

    bool IsStudentCheckedIn(const string &studentID);

    bool IDExists(const string &studentID);

    string Get_ID();

    void checkUserInfo(const string &userID);

    void deleteUser(const string &userID);

    void checkUserInfoALL();

    void checkUserInfoByName(const string &userName);


    void DealAccommodationRequests();

    // 处理通过的申请
    void approveRequest(const std::string &requestID);

    // 处理拒绝的申请
    void rejectRequest(const std::string &requestID);

    // 更新审批状态
    void updateApprovalStatus(const std::string &requestID, const std::string &status);

    // 处理入住申请
    void handleCheckInRequest(const std::string &requestID);

    // 处理换宿申请
    void handleRoomChangeRequest(const std::string &requestID);

    // 处理退宿申请
    void handleCheckOutRequest(const std::string &requestID);

    // 验证待处理的申请ID（是否存在且状态为“待审批”）
    void viewAccommodationRequests(const std::string &requestID = "");

    // 检查用户是否存在
};

#endif // USERMANAGER_H
