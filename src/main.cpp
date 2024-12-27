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


// 查看通知
void viewNotifications(const string &stuID);

void manageUsers();

void mamageRooms();

void checkUserInfo(const string &userID);

void generateReports();

void handleRepairRequests();


void adminLogin();

void dormManageMenu();

void studentLogin();


//cout << "数据库成功链接\n数据已更新" << endl;
//userManager->DealAccommodationRequests();
// userManager->getAllUsers();
//adminMenu();
//userManager->arrangeAccommodation();

//userManager->deleteDormitory();
//studentMenu("t2");
//adminMenu();
//userManager->manageRooms();
// 主程序入口
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choice;

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
    while (gender != "男" && gender != "女")
    {
        cout << "请输入性别(男/女): ";
        cin >> gender;
    }
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
        cout << "4. 房间管理\n";
        cout << "0. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addDormitory();
                break;
            case 2:
                userManager->deleteDormitory();
            //deleteDormitory();
                break;
            case 3:
                userManager->viewAllDormitories();
                break;
            case 4:
                userManager->manageRooms();
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
    cin.ignore();
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

// void deleteDormitory_old()
// {
//     cin.ignore();
//     string dormitoryName;
//     viewDormitories();
//     // 检查宿舍楼名称输入是否存在
//     cout << "请输入要删除的宿舍楼名称：";
//     while (true)
//     {
//         getline(cin, dormitoryName); // 使用getline()读取宿舍楼名称
//         if (dormitoryName == "exit ") return;
//         if (!dormitoryName.empty())
//         {
//             // 检查宿舍楼是否存在
//             if (userManager->dormitoryExistsByName(dormitoryName))
//             {
//                 break; // 存在，跳出循环
//             } else
//             {
//                 cout << "宿舍楼名称不存在，请重新输入有效的名称：";
//             }
//         } else
//         {
//             cout << "宿舍楼名称不能为空，请输入：";
//         }
//     }
//
//     // 检查宿舍楼是否有房间有学生入住
//     string checkRoomsSql = R"(
//         SELECT 1
//         FROM rooms r
//         JOIN dormitories d ON r.dormitoryID = d.dormitoryID
//         WHERE d.name = ')" + dormitoryName + "' AND r.occupied > 0 LIMIT 1;)";
//     userManager->Query(checkRoomsSql);
//     // 调用 UserManager 的方法，检查是否有学生入住
//     if (userManager->hasStudentsInDormitoryRooms(checkRoomsSql))
//     {
//         cout << "该宿舍楼下有房间已被学生入住。请先处理这些学生的退宿，直到房间为空。\n";
//         return; // 如果有学生入住，返回，不删除宿舍楼
//     }
//
//     // 构造SQL语句来删除宿舍楼
//     string sql = "DELETE FROM dormitories WHERE name = '" + dormitoryName + "';";
//
//     // 执行SQL语句
//     userManager->execute(sql);
//
//     cout << "宿舍楼 '" << dormitoryName << "' 删除成功。\n";
// }


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
                userManager->viewDormitoryInfo(stuID); // 查看宿舍楼和房间信息
                break;
            case 2:
                userManager->applyMoveIn(stuID); // 申请入住
                break;
            case 3:
                userManager->applyMoveOut(stuID); // 申请退宿
                break;
            case 4:
                userManager->requestRoomChange(stuID); // 请求换宿
                break;
            case 5:
                userManager->submitRepairRequest(stuID); // 提交维修请求
                break;
            case 6:
                userManager->viewNotifications(stuID); // 查看通知
                break;
            case 7:
                userManager->viewRequests(stuID); // 查看请求
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


// 提交维修请求


// 查看通知








