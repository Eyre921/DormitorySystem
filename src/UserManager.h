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
    bool registerUser(const string &userID, const string &password, const string &name,
                      const string &gender, const string &contactInfo, bool isCheckedIn, bool isAdmin);

    void addDormitory();

    void AddUser();

    void studentRegister();

    void execute(const string &SQL);

    // 获取所有用户
    void GetAllUsers();

    void Query(const string &SQL);

    bool QueryExists(const string &SQL);


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

    void submitRepairRequest(const string &stuID);

    void viewNotifications(const string &stuID);

    void viewRequests(const string &stuID);

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
    void approveRequest(const string &requestID);

    // 处理拒绝的申请
    void rejectRequest(const string &requestID);

    // 更新审批状态
    void updateApprovalStatus(const string &requestID, const string &status);

    // 处理入住申请
    void handleCheckInRequest(const string &requestID);

    // 处理换宿申请
    void handleRoomChangeRequest(const string &requestID);

    // 处理退宿申请
    void handleCheckOutRequest(const string &requestID);

    // 验证待处理的申请ID（是否存在且状态为“待审批”）
    void viewAccommodationRequests(const string &requestID = "");

    void deleteDormitory();

    void deleteRoom(const string &selectedRoomID);

    bool checkRoomOccupancy(const string &dormitoryName, const string &roomNumber);

    void viewAllDormitories();

    void viewAllRooms(const string &dormitoryID);

    void ViewStudentsInRoom(const string &dormitoryID, const string &roomNumber);

    void modifyRoomInfo(const string &selectedRoomID, int capacity);

    void viewDormitoryInfo(const string &stuID);

    void applyMoveIn(const string &stuID);

    void applyMoveOut(const string &stuID);

    void manageRooms();

    // 检查用户是否存在
};

#endif // USERMANAGER_H
