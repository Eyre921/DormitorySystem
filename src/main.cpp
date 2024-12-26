#include <iostream>
#include <windows.h>
#include <UserManager.h>
#include <limits>
#include <string>
#include "globals.h"//全局指针
using namespace std;


// 函数声明
void showMainMenu();

void userLogin();

void studentRegister();

void studentMenu(const string &stuID);

void adminMenu();

void manageDormitories();

void addDormitory();

void deleteDormitory();

void viewDormitories();

void studentLoginMenu();

// 申请入住
void applyMoveIn(const string &stuID);

// 申请退宿
void applyMoveOut(const string &stuID);

// 请求换宿
void requestRoomChange(const string &stuID);

// 提交维修请求
void submitRepairRequest(const string &stuID);

// 查看通知
void viewNotifications(const string &stuID);

void manageUsers();

void checkUserInfo(const string &userID);

void generateReports();

void handleRepairRequests();

void viewDormitoryInfo(const string &stuID);


void submitRepairRequest();

void adminLogin();

void dormManageMenu();

void studentLogin();

void viewRequests(const string &stuID);

void viewNotifications();


// 主程序入口
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choice;
    cout << "数据库成功链接\n数据已更新" << endl;
    //userManager->DealAccommodationRequests();
    // userManager->getAllUsers();
    //adminMenu();
    //userManager->arrangeAccommodation();
    //userManager->arrangeCheckOut("2031");
    //userManager->requestRoomChange("2031");
    // applyMoveIn("2031");
    // applyMoveOut("2031");
    while (true)
    {
        cout << "\n---- 主菜单 ----\n";
        cout << "1. 学生菜单\n";
        cout << "2. 管理员菜单\n";
        cout << "0. 退出\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                studentLoginMenu(); // 学生登录
                break;
            case 2:
                adminLogin(); // 管理员登录
                break;
            case 0:
                cout << "正在退出程序……\n";
                return 0;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

void studentLoginMenu()
{
    int choice;
    cout << "\n---- 学生菜单 ----\n";
    cout << "1. 学生登录\n";
    cout << "2. 学生注册\n";
    cout << "0. 退出\n";
    cout << "请输入你的选择: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            studentLogin(); // 学生登录
            break;
        case 2:
            studentRegister(); // 学生注册
            break;
        case 0:
            return;
        default:
            cout << "无效选择，请重新输入。\n";
            break;
    }
}

void studentLogin()
{
    string studentID, password;
    cout << "\n---- 学生登录 ----\n";
    cout << "请输入学号: ";
    cin >> studentID;
    cout << "请输入密码: ";
    cin >> password;

    // 调用 UserManager 中的 loginUser 方法，验证登录
    if (userManager->loginUser(studentID, password, "0"))
    {
        size_t str_len = studentID.size();
        if (str_len < 6)
        {
            if (studentID == password)
            {
                //进入修改密码界面
                cout << "您的密码是默认密码，请修改\n";
                userManager->UserPasswordChange(studentID);
            }
        } else
        {
            if (studentID.substr(str_len - 6, 6) == password)
            {
                //进入修改密码界面
                cout << "您的密码是默认密码，请修改\n";
                userManager->UserPasswordChange(studentID);
            }
        }
        studentMenu(studentID); // 登录成功后跳转到学生菜单
    } else
    {
        cout << "学号或密码错误！\n";
    }
}

// 管理员登录功能
void adminLogin()
{
    string adminID, password;
    cout << "\n---- 管理员登录 ----\n";
    cout << "请输入管理员账号: ";
    cin >> adminID;
    cout << "请输入密码: ";
    cin >> password;

    if (userManager->loginUser(adminID, password, "1"))
    {
        adminMenu();;
    } else
    {
        cout << "账号或密码错误！\n";
    }
}

void studentRegister()
{
    string studentID, password, name, gender, contactInfo;
    cout << "\n---- 学生注册 ----\n";
    cout << "请输入学号: ";
    cin >> studentID;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入性别: ";
    cin >> gender;
    cout << "请输入联系方式: ";
    cin >> contactInfo;
    userManager->registerUser(studentID, password, name, gender, contactInfo, false, false);
}

void adminMenu()
{
    int choice;
    while (true)
    {
        cout << "\n---- 管理员菜单 ----\n";
        cout << "1. 舍楼管理中心\n";
        cout << "2. 用户管理中心\n";
        cout << "3. 报表生成模块\n";
        cout << "4. 维修处理中心\n";
        cout << "5. 住宿管理中心\n";
        cout << "0. 退出登录\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                manageDormitories(); // 管理宿舍楼
                break;
            case 2:
                manageUsers(); // 管理用户
                break;
            case 3:
                generateReports(); // 生成报表
                break;
            case 4:
                handleRepairRequests(); // 处理维修请求
                break;
            case 5:
                dormManageMenu();
            // TODO
                break;
            case 0:
                cout << "正在退出登录...\n";
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员管理用户
void manageUsers()
{
    string ID;
    int choice;
    while (true)
    {
        cout << "\n---- 管理用户 ----\n";
        cout << "1. 添加用户\n";
        cout << "2. 删除用户\n";
        cout << "3. 查看用户信息(通过学号)\n";
        cout << "4. 查看用户信息(通过姓名)\n";
        cout << "5. 查看全部用户信息\n";
        cout << "0. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                int new_num;
                cout << "请输入需要添加的用户数量（输入0返回上一级）：";
                cin >> new_num;
                if (new_num == 0)
                {
                    return;
                } else
                {
                    for (int i = 1; i <= new_num; i++)
                    {
                        string userID;
                        cout << "请输入第" << i << "位用户的学号：";
                        while (true)
                        {
                            cin >> userID;
                            if (userManager->IDExists(userID))
                            {
                                cout << "该学号已经被注册！请重新输入学号:" << endl;
                                continue;
                            }
                            break;
                        }

                        size_t str_len = userID.size();
                        string password;
                        if (str_len <= 6)
                        {
                            password = userID;
                        } else
                        {
                            //默认密码为学号后6位
                            password = userID.substr(str_len - 6, 6);
                        }
                        string name;
                        cout << "请输入第" << i << "位用户的姓名：";
                        cin >> name;
                        string gender;
                        while (gender != "男" && gender != "女")
                        {
                            cout << "请输入第" << i << "位用户的性别：（男/女）";
                            cin >> gender;
                        }
                        string contactInfo;
                        cout << "请输入第" << i << "位用户的联系方式：";
                        cin >> contactInfo;
                        userManager->registerUser(userID, password, name, gender, contactInfo, false, false);
                    }
                }
                break;
            case 2:
                cin.ignore();
                ID = userManager->Get_ID();
                if (ID == "exit") break;
                userManager->deleteUser(ID);
                break;
            case 3:
                cin.ignore();
                ID = userManager->Get_ID();
                if (ID == "exit") break;
                userManager->checkUserInfo(ID);
                break;
            case 4:
                cin.ignore();
                cout << "请输入查询的名字：" << endl;
                getline(cin, ID);
                if (ID == "exit") break;
                userManager->checkUserInfoByName(ID);
                break;
            case 5:
                userManager->checkUserInfoALL();
                break;


            case 0:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 住宿管理中心
void dormManageMenu()
{
    string ID;
    int choice;
    while (true)
    {
        cout << "\n---- 宿舍管理 ----\n";

        cout << "1. 安排住宿\n";
        cout << "2. 安排退宿\n";
        cout << "3. 申请处理\n";
        cout << "0. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cin.ignore();
                while (true)
                {
                    ID = userManager->Get_ID();
                    // 检查是否已经入住
                    if (userManager->IsStudentCheckedIn(ID))
                    {
                        cout << "该学生已入住，请重新选择其他学生。\n";
                        continue;
                    }
                    break;
                }
                if (ID == "exit") break;
                userManager->arrangeAccommodation(ID);
                break;
            case 2:
                cin.ignore();
                while (true)
                {
                    ID = userManager->Get_ID();
                    // 检查是否已经入住
                    if (!userManager->IsStudentCheckedIn(ID))
                    {
                        cout << "该学生未入住，请重新选择其他学生。\n";
                        continue;
                    }
                    break;
                }
                if (ID == "exit") break;
                userManager->arrangeCheckOut(ID);
                break;
            case 3:
                userManager->DealAccommodationRequests();
                break;
            case 0:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员生成报表
void generateReports()
{
    int choice;
    while (true)
    {
        cout << "\n---- 生成报表 ----\n";
        cout << "1. 生成宿舍使用情况报表\n";
        cout << "2. 生成入住率报表\n";
        cout << "3. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // TODO: 生成宿舍使用情况报表
                cout << "生成宿舍使用情况报表 - 功能开发中。\n";
                break;
            case 2:
                // TODO: 生成入住率报表
                cout << "生成入住率报表 - 功能开发中。\n";
                break;
            case 3:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员处理维修请求
void handleRepairRequests()
{
    int choice;
    while (true)
    {
        cout << "\n---- 处理维修请求 ----\n";
        cout << "1. 查看所有维修请求\n";
        cout << "2. 更新维修请求状态\n";
        cout << "3. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // TODO: 查看维修请求
                cout << "查看维修请求 - 功能开发中。\n";
                break;
            case 2:
                // TODO: 更新维修请求状态
                cout << "更新维修请求状态 - 功能开发中。\n";
                break;
            case 3:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

void manageDormitories()
{
    int choice;
    while (true)
    {
        cout << "\n---- 管理宿舍楼 ----\n";
        cout << "1. 添加宿舍楼\n";
        cout << "2. 删除宿舍楼\n";
        cout << "3. 查看宿舍楼信息\n";
        cout << "0. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addDormitory();
                break;
            case 2:
                deleteDormitory();
                break;
            case 3:
                viewDormitories();
                break;
            case 0:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

void addDormitory()
{
    string dormitoryName, sex, position;
    int roomCount, bedCount;

    // 输入宿舍楼名称并检查是否已存在
    cout << "请输入宿舍楼名称：";
    while (true)
    {
        getline(cin, dormitoryName);
        if (!dormitoryName.empty())
        {
            if (userManager->dormitoryExistsByName(dormitoryName))
            {
                cout << "宿舍楼名称已存在，请重新输入一个唯一的名称：";
            } else
            {
                break;
            }
        } else
        {
            cout << "宿舍楼名称不能为空，请输入：";
        }
    }

    // 输入宿舍楼性别并验证
    cout << "请输入宿舍楼性别（男/女）：";
    while (true)
    {
        cin >> sex;
        if (sex == "男" || sex == "女")
        {
            break;
        } else
        {
            cout << "性别输入无效，请输入 '男' 或 '女'：";
        }
    }

    // 输入宿舍楼位置
    cout << "请输入宿舍楼位置：";
    cin.ignore(); // 忽略前一个输入留下的换行符
    getline(cin, position);

    // 插入宿舍楼信息
    string sql = "INSERT INTO dormitories (name, sex, position) VALUES ('" + dormitoryName + "', '" + sex + "', '" +
                 position + "');";
    userManager->execute(sql);

    // 获取新插入的宿舍楼ID（这里假设为1）
    int dormitoryID = userManager->getDormitoryIDByName(dormitoryName);

    // 输入房间数量和床位数
    cout << "请输入房间数量：";
    cin >> roomCount;
    cout << "请输入每个房间的床位数：";
    cin >> bedCount;

    // 自动生成房间
    for (int i = 1; i <= roomCount; i++)
    {
        string roomNumber = "N" + to_string(i); // 自动生成房间号，形如 R1, R2, ...

        // 构造SQL语句插入房间信息
        string roomSql = "INSERT INTO rooms (dormitoryID, roomNumber, capacity) VALUES (" + to_string(dormitoryID) +
                         ", '" + roomNumber + "', " + to_string(bedCount) + ");";
        userManager->execute(roomSql);
    }

    cout << "宿舍楼和房间信息添加成功！\n";
}

void deleteDormitory()
{
    string dormitoryName;

    // 检查宿舍楼名称输入是否存在
    cout << "请输入要删除的宿舍楼名称：";
    while (true)
    {
        getline(cin, dormitoryName); // 使用getline()读取宿舍楼名称

        if (!dormitoryName.empty())
        {
            // 检查宿舍楼是否存在
            if (userManager->dormitoryExistsByName(dormitoryName))
            {
                break; // 存在，跳出循环
            } else
            {
                cout << "宿舍楼名称不存在，请重新输入有效的名称：";
            }
        } else
        {
            cout << "宿舍楼名称不能为空，请重新输入：";
        }
    }

    // 检查宿舍楼是否有房间有学生入住
    string checkRoomsSql = R"(
        SELECT 1
        FROM rooms r
        JOIN dormitories d ON r.dormitoryID = d.dormitoryID
        WHERE d.name = ')" + dormitoryName + "' AND r.occupied > 0 LIMIT 1;)";
    userManager->Query(checkRoomsSql);
    // 调用 UserManager 的方法，检查是否有学生入住
    if (userManager->hasStudentsInDormitoryRooms(checkRoomsSql))
    {
        cout << "该宿舍楼下有房间已被学生入住。请先处理这些学生的退宿，直到房间为空。\n";
        return; // 如果有学生入住，返回，不删除宿舍楼
    }

    // 构造SQL语句来删除宿舍楼
    string sql = "DELETE FROM dormitories WHERE name = '" + dormitoryName + "';";

    // 执行SQL语句
    userManager->execute(sql);

    cout << "宿舍楼 '" << dormitoryName << "' 删除成功。\n";
}

void viewDormitories()
{
    // 构造SQL语句
    string sql = R"(
            SELECT d.name, d.sex, d.position,
                   COUNT(r.roomID) AS 房间数,
                   SUM(CASE WHEN r.occupied = r.capacity THEN 1 ELSE 0 END) AS 是否已满
            FROM dormitories d
            LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
            GROUP BY d.dormitoryID;
        )";

    // 执行SQL语句
    userManager->Query(sql);
}

void studentMenu(const string &stuID)
{
    int choice;
    while (true)
    {
        cout << "\n---- 学生菜单 ----\n";
        cout << "1. 查看宿舍楼和房间信息\n";
        cout << "2. 申请入住\n";
        cout << "3. 申请退宿\n";
        cout << "4. 请求换宿\n";
        cout << "5. 提交维修请求\n";
        cout << "6. 查看通知\n";
        cout << "7. 查看请求\n";
        cout << "8. 修改密码\n";
        cout << "0. 退出登录\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        // 清除输入缓冲区，以防止输入错误导致无限循环
        if (cin.fail())
        {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
            cout << "输入无效，请输入数字。\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                viewDormitoryInfo(stuID); // 查看宿舍楼和房间信息
                break;
            case 2:
                applyMoveIn(stuID); // 申请入住
                break;
            case 3:
                applyMoveOut(stuID); // 申请退宿
                break;
            case 4:
                requestRoomChange(stuID); // 请求换宿
                break;
            case 5:
                submitRepairRequest(stuID); // 提交维修请求
                break;
            case 6:
                viewNotifications(stuID); // 查看通知
                break;
            case 7:
                viewRequests(stuID); // 查看请求
                break;
            case 8:
                userManager->UserPasswordChange(stuID); // 修改密码
                break;
            case 0:
                cout << "正在退出登录...\n";
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 申请入住
void applyMoveIn(const string &stuID)
{
    if (userManager->IsStudentCheckedIn(stuID))
    {
        cout << "您已经入住！" << endl;
        return;
    }
    // 构建 SQL 查询语句，仅插入学生 ID 和申请类型
    string sql = "INSERT INTO accommodation_requests (studentID, requestType) "
                 "VALUES ('" + stuID + "', '入住');";

    // 执行 SQL 语句
    userManager->execute(sql);
    cout << "申请入住成功" << endl;
}

// 申请退宿
void applyMoveOut(const string &stuID)
{
    if (!userManager->IsStudentCheckedIn(stuID))
    {
        cout << "您尚未入住！" << endl;
        return;
    }
    // 构建 SQL 查询语句，仅插入学生 ID 和申请类型
    string sql = "INSERT INTO accommodation_requests (studentID, requestType) "
                 "VALUES ('" + stuID + "', '退宿');";

    // 执行 SQL 语句
    userManager->execute(sql);
    cout << "申请退宿成功" << endl;
}

// 请求换宿
void requestRoomChange(const string &stuID)
{
    userManager->requestRoomChange(stuID);
}

// 提交维修请求
void submitRepairRequest(const string &stuID) {}

// 查看通知
void viewNotifications(const string &stuID) {}


void viewRequests(const string &stuID)
{
    string sql =
            "SELECT requestID AS \"申请ID\", requestType AS \"申请类型\", status AS \"申请状态\",dormitoryName AS \"宿舍楼名称\", "
            "roomNumber AS \"房间号\",  requestTime AS \"申请时间\", "
            "approveTime AS \"审批时间\", note AS \"备注\" "
            "FROM accommodation_requests "
            "WHERE studentID = '" + stuID + "' "
            "ORDER BY requestTime DESC;";
    userManager->Query(sql);
}


// 学生查看宿舍信息
void viewDormitoryInfo(const string &stuID)
{
    if (userManager->IsStudentCheckedIn(stuID))
    {
        string sql = "SELECT "
                     "    d.name AS 宿舍楼,           -- 宿舍楼名称\n"
                     "    r.roomNumber AS 房间号,        -- 房间号\n"
                     "    r.capacity AS 房间容量,       -- 房间容量\n"
                     "    r.occupied AS 已入住人数,       -- 已入住人数\n"
                     "    r.repair_status AS 维修状态   -- 维修状态\n"
                     "FROM "
                     "    student_rooms sr\n"
                     "JOIN "
                     "    rooms r ON sr.roomID = r.roomID   -- 连接房间表\n"
                     "JOIN "
                     "    dormitories d ON r.dormitoryID = d.dormitoryID -- 连接宿舍楼表\n"
                     "JOIN "
                     "    users u ON sr.studentID = u.userID -- 连接学生表\n"
                     "WHERE "
                     "    u.userID = '" + stuID + "';"; // 使用学生ID作为参数传递

        // 调用Query方法，执行SQL查询
        string sql2 = "SELECT recordType AS 记录类型, eventTime AS 时间, note AS 备注 "
                      "FROM check_in_out_records "
                      "WHERE studentID = '" + stuID + "' "
                      "ORDER BY recordID DESC LIMIT 1;";

        userManager->Query(sql);
        userManager->Query(sql2);
    } else
    {
        string xuan;
        cout << "您暂未被安排住宿，是否申请？(请输入yes/no)" << endl;
        cin.ignore();
        getline(cin, xuan);
        if (xuan == "yes")
        {
            applyMoveIn(stuID);
        }
    }
}


// 学生提交维修请求
void submitRepairRequest()
{
    cout << "提交维修请求 - 功能开发中。\n";
}

// 学生查看通知
void viewNotifications()
{
    cout << "查看通知 - 功能开发中。\n";
}
