#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "Database.h"
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

    int getChoice();

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
    void modifyRoomInfo(const string &selectedRoomID, int capacity);

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

    // 查看住宿记录
    void viewCheckInOutRecords(const string &studentID = "");

    void checkUserNotCheckedIn();

    void handleRepairRequests();

    void generateAccommodationRateReport();

    // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 //

    // 学生注册
    void studentRegister();

    // 1. 查看宿舍楼和房间信息
    void viewDormitoryInfo(const string &stuID);

    bool hasPendingApplication(const string &studentID);

    // 2. 申请入住
    void applyMoveIn(const string &stuID);

    // 3. 申请退宿
    void applyMoveOut(const string &stuID);

    // 4. 请求换宿
    void requestRoomChange(const string &studentID);

    // 5. 提交维修请求
    void createRepairRequest(const string &studentID);

    // 6. 查看通知
    void viewNotifications(const string &stuID);

    // 7. 查看请求
    void viewRequests(const string &stuID);

    void viewApprovingRequests(const string &stuID);
};

#endif // USERMANAGER_H
/*
以下是对当前文件的代码找茬：
在分析了提供的UserManager.h源代码后，我将从以下几个方面来列出可能存在的问题：漏洞、缺陷、性能、安全、代码质量。

漏洞
SQL注入风险：query、execute、queryExists等函数直接接受SQL字符串作为参数，没有对输入进行任何过滤或转义，这可能导致SQL注入攻击。
未验证的用户输入：如loginUser、registerUser等函数中，用户输入的ID、密码等信息未进行有效性检查，可能导致非法数据进入系统。
缺陷
硬编码的数据库连接：Database db;直接在类中实例化，缺乏灵活性，如果需要更换数据库或配置，修改起来会非常麻烦。
函数命名不规范：部分函数名如getChoice、viewAllRooms等，未能清晰表达其功能，容易引起误解。
性能
频繁的数据库操作：如getAllUsers、viewAllDormitories等函数可能会导致大量的数据库查询，若不加以优化，可能会影响系统性能。
缺乏缓存机制：对于一些不常变动的数据，如宿舍信息、用户信息等，可以考虑使用缓存来减少数据库的访问频率。
安全
明文存储密码：registerUser函数中没有提到密码的加密存储，这可能导致用户密码以明文形式存储在数据库中，存在严重的安全隐患。
缺乏访问控制：如deleteUser、addDormitory等敏感操作，没有对调用者进行权限验证，可能导致未经授权的操作。
代码质量
使用命名空间：using namespace std;在头文件中使用是不推荐的，这可能会导致命名冲突。
注释过多且无意义：代码中有大量重复的注释，如“数据库功能”、“通用功能”等，这些注释没有提供有用的信息，反而增加了阅读负担。
函数职责不单一：如arrangeAccommodation、quickArrangeAccommodation等函数，既处理业务逻辑又涉及数据库操作，违反了单一职责原则。
以上是对UserManager.h源代码的初步分析，建议在实际开发中针对上述问题进行改进，以提高代码的安全性、可维护性和性能。
 */
