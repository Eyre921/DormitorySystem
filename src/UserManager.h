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

    // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 //

    // 查询并打印
    void query(const string &SQL);

    // 执行
    void execute(const string &SQL);

    // 查询但不打印
    bool queryExists(const string &SQL);


    // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 //

    // 一键获取所有用户信息
    void getAllUsers();

    // 获取并返回ID
    string get_ID();

    // ID是否存在（包括管理员）
    bool IDExists(const string &studentID);

    // 宿舍是否存在
    bool dormitoryExistsByName(const string &dormitoryName);

    // 学生ID是否存在（不包括管理员）
    bool studentExistsByID(const string &ID);

    int getDormitoryIDByName(const string &dormitoryName);

    // 用户登录
    bool loginUser(const string &userID, const string &password, const string &isAdmin);

    // 用户注册
    bool registerUser(const string &userID, const string &password, const string &name, const string &gender,
                      const string &contactInfo, bool isCheckedIn, bool isAdmin);

    // 修改密码
    bool userPasswordChange(const string &userID);

    // 是否入住
    bool isStudentCheckedIn(const string &studentID);

    // 选择有效的宿舍（通过引用修改）
    void selectValidRoom(const string &studentID, string &dormitoryName, string &roomChoice);

    // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 //

    // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 //
    // 添加宿舍楼
    void addDormitory();

    // 删除宿舍楼
    void deleteDormitory();


    // 查看所有宿舍楼信息
    void viewAllDormitories();

    // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 //

    // 查看选定宿舍楼的所有房间信息和入住学生
    void viewAllRooms(const string &dormitoryName);

    // 房间管理菜单
    void manageRooms();

    // 1. 查看入住信息
    void viewStudentsInRoom(const string &dormitoryName, const string &roomNumber);

    // 2. 删除房间
    void deleteRoom(const string &selectedRoomID);

    // 3. 修改房间信息
    void modifyRoomInfo(const string &selectedRoomID, const int capacity);

    // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 //
    // 添加用户
    void addUser();

    // 删除用户
    void deleteUser(const string &userID);

    // 通过ID查询用户信息
    void checkUserInfo(const string &userID);

    // 通过姓名查询用户信息（支持模糊查询）
    void checkUserInfoByName(const string &userName);

    // 查询所有用户信息
    void checkUserInfoALL();

    // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 //
    // 1. 安排住宿
    void arrangeAccommodation(const string &studentID);

    // 一键入住
    void quickArrangeAccommodation(const string &studentID, const string &dormitoryName,
                                   const string &roomChoice, const string &note);

    // 2. 安排退宿
    void arrangeCheckOut(const string &studentID);

    // 一键退宿
    void quickArrangeCheckOut(const string &studentID, const string &note);

    // 3. 处理学生申请
    void dealAccommodationRequests();

    // 更新审批状态
    void updateApprovalStatus(const string &requestID, const string &status);

    // 查看申请（输入为空则查询所有，输入为指定则查询指定）
    void viewAccommodationRequests(const string &requestID = "");


    // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 //

    // 学生注册
    void studentRegister();

    // 1. 查看宿舍楼和房间信息
    void viewDormitoryInfo(const string &stuID);

    // 2. 申请入住
    void applyMoveIn(const string &stuID);

    // 3. 申请退宿
    void applyMoveOut(const string &stuID);

    // 4. 请求换宿
    void requestRoomChange(const string &studentID);

    // 5. 提交维修请求
    void submitRepairRequest(const string &stuID);

    // 6. 查看通知
    void viewNotifications(const string &stuID);

    // 7. 查看请求
    void viewRequests(const string &stuID);

    // 检查用户是否存在
};

#endif // USERMANAGER_H
