#include <iostream>
#include <windows.h>
#include <UserManager.h>
#include <limits>
#include <string>
#include "globals.h"//全局指针
#include "specialPrint.h"
#include<conio.h>
using namespace std;


// 函数声明


void studentLogin();

void studentLoginMenu();

void studentMenu(const string &stuID);

void applyAccommodationChange(const string &stuID);

void adminLogin();

void adminMenu();

void manageDormitories();

void manageUsers();

void generateReports();

void dormManageMenu();

int getChoice();

//adminMenu();
//studentMenu("t2");

// 主程序入口
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand((unsigned) time(NULL)); //根据当前时间来生成随机数
    loading("正在启动宿舍管理系统", 50, 30);
    system("cls");
    openPrint();
    system("CLS");
    while (true)
    {
        slowPrint("●主菜单●", 30, 0);
        menuPrint("UP", 30);
        menuPrint("1、学生菜单", 30);
        menuPrint("2、管理员菜单", 30);
        menuPrint("0、退出", 30);
        menuPrint("DOWN", 30);
        slowPrint("请输入您的选择：", 30, -1);
        // cout << "\n---- 主菜单 ----\n";
        // cout << "1. 学生菜单\n";
        // cout << "2. 管理员菜单\n";
        // cout << "0. 退出\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();

        switch (choice)
        {
            case 1:
                system("cls");
                studentLoginMenu(); // 学生登录
                break;
            case 2:
                system("cls");
                adminLogin(); // 管理员登录
                break;
            case 0:
                slowPrint("正在退出程序……", 40, -1);
                Sleep(2000);
            //cout << "正在退出程序……\n";
                return 0;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

int getChoice()
{
    int choice;

    while (true)
    {
        cin >> choice;
        if (choice > 11)
        {
            cout << "输入无效，请输入有效数字：";
            continue;
        }
        if (cin.fail()) // 清除输入缓冲区，以防止输入错误导致无限循环
        {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
            cout << "输入无效，请输入有效数字：";
            continue;
        }
        break;
    }

    return choice;
}

// 学生登录菜单
void studentLoginMenu()
{
    slowPrint("●学生菜单●", 30, 0);
    menuPrint("UP", 30);
    menuPrint("1、学生登录", 30);
    menuPrint("2、学生注册", 30);
    menuPrint("0、退出", 30);
    menuPrint("DOWN", 30);
    slowPrint("请输入您的选择：", 30, -1);
    // cout << "\n---- 学生菜单 ----\n";
    // cout << "1. 学生登录\n";
    // cout << "2. 学生注册\n";
    // cout << "0. 退出\n";
    // cout << "请输入你的选择: ";
    int choice = getChoice();

    switch (choice)
    {
        case 1:
            system("cls");
            studentLogin(); // 学生登录
            break;
        case 2:
            system("cls");
            userManager->studentRegister(); // 学生注册
            break;
        case 0:
            system("cls");
            return;
        default:
            cout << "无效选择，请重新输入。\n";
            break;
    }
}

// 学生登录
void studentLogin()
{
    string studentID, password;
    slowPrint("●学生登录●", 30, 0);
    //cout << "\n---- 学生登录 ----\n";
    slowPrint("请输入学号: ", 30, -1);
    //cout << "请输入学号: ";
    cin >> studentID;
    slowPrint("请输入密码(输入*可以查看被隐藏的密码,回车确认): ", 30, -1);
    //cout << "请输入密码: ";
    clearScreen(0, 0);
    // cout<<"         ●学生登录●\n请输入学号："+studentID+"请输入密码(输入*可以查看被隐藏的密码): " ;
    // system("cls");
    password = passwordHide("         ●学生登录●\n请输入学号：" + studentID + "\n请输入密码(输入*可以查看被隐藏的密码,回车确认): ");
    cout << endl;

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
                userManager->userPasswordChange(studentID);
            }
        } else
        {
            if (studentID.substr(str_len - 6, 6) == password)
            {
                //进入修改密码界面
                cout << "您的密码是默认密码，请修改\n";
                userManager->userPasswordChange(studentID);
            }
        }
        system("cls");
        loading("正在登录中", 50, 20);
        slowPrint("登录成功！", 50, 0);
        Sleep(2000);
        system("cls");
        studentMenu(studentID); // 登录成功后跳转到学生菜单
    } else
    {
        cout << "学号或密码错误！\n";
        Sleep(1000);
        system("cls");
        return;
    }
}

// 学生菜单
void studentMenu(const string &stuID)
{
    while (true)
    {
        slowPrint("●学生菜单●", 40, 0);
        menuPrint("UP", 40);
        menuPrint("1、查看宿舍楼和房间信息", 40);
        menuPrint("2、申请住宿调整", 40);
        menuPrint("3、提交维修请求", 40);
        menuPrint("4、查看通知", 40);
        menuPrint("5、查看请求", 40);
        menuPrint("6、修改密码", 40);
        menuPrint("0、退出登录", 40);
        menuPrint("DOWN", 40);
        slowPrint("请输入您的选择：", 40, -1);
        // cout << "\n---- 学生菜单 ----\n";
        // cout << "1. 查看宿舍楼和房间信息\n";
        // cout << "2. 申请住宿调整\n";
        // cout << "3. 提交维修请求\n";
        // cout << "4. 查看通知\n";
        // cout << "5. 查看请求\n";
        // cout << "6. 修改密码\n";
        // cout << "0. 退出登录\n";
        // cout << "请输入你的选择: ";

        int choice = getChoice();
        // 清除输入缓冲区，以防止输入错误导致无限循环


        switch (choice)
        {
            case 1:
                system("cls");
                userManager->viewDormitoryInfo(stuID); // 查看宿舍楼和房间信息
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                applyAccommodationChange(stuID); // 申请住宿调整
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 3:
                if (!userManager->isStudentCheckedIn(stuID))
                {
                    cout << "您未入住！" << endl;
                    system("cls");
                    break;
                }
                system("cls");
                userManager->createRepairRequest(stuID); // 提交维修请求
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                userManager->viewNotifications(stuID); // 查看通知
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                userManager->viewRequests(stuID); // 查看请求
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 6:
                system("cls");
                userManager->userPasswordChange(stuID); // 修改密码
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 0:
                slowPrint("正在退出登录..", 40, -1);
            //cout << "正在退出登录...\n";
                Sleep(1000);
                system("cls");
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

void applyAccommodationChange(const string &stuID)
{
    while (true)
    {
        if (userManager->hasPendingApplication(stuID))
        {
            cout << "您还有待审批的请求！" << endl;
            userManager->viewApprovingRequests(stuID);
            return;
        }
        slowPrint("●申请宿舍调整●", 30, 0);
        menuPrint("UP", 30);
        menuPrint("1、申请入住", 30);
        menuPrint("2、申请退宿", 30);
        menuPrint("3、请求换宿", 30);
        menuPrint("0、退出", 30);
        menuPrint("DOWN", 30);
        slowPrint("请输入您的选择：", 30, -1);
        // cout << "\n---- 申请宿舍调整 ----\n";
        //
        // cout << "1. 申请入住\n";
        // cout << "2. 申请退宿\n";
        // cout << "3. 请求换宿\n";
        //
        // cout << "0. 退出\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();

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
                system("cls");
                userManager->applyMoveIn(stuID); // 申请入住
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                userManager->applyMoveOut(stuID); // 申请退宿
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                userManager->requestRoomChange(stuID); // 请求换宿
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 0:
                cout << "已返回。\n";
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员登录
void adminLogin()
{
    string adminID, password;
    slowPrint("●管理员登录●", 30, 0);
    slowPrint("请输入管理员账号: ", 30, -1);
    cin >> adminID;
    slowPrint("请输入密码(输入*可以查看被隐藏的密码,回车确认): ", 30, -1);
    clearScreen(0, 0);
    password = passwordHide("        ●管理员登录●\n请输入管理员账号：" + adminID + "\n请输入密码(输入*可以查看被隐藏的密码,回车确认): ");
    cout << endl;

    if (userManager->loginUser(adminID, password, "1"))
    {
        system("cls");
        loading("正在登录中", 50, 30);
        slowPrint("登录成功!", 50, 0);
        Sleep(2000);
        system("cls");
        adminMenu();;
    } else
    {
        cout << "账号或密码错误！\n";
        Sleep(1000);
        system("cls");
    }
}

// 管理员菜单
void adminMenu()
{
    while (true)
    {
        slowPrint("●管理员菜单●", 30, 0);
        menuPrint("UP", 30);
        menuPrint("1、舍楼管理中心", 30);
        menuPrint("2、用户管理中心", 30);
        menuPrint("3、报表生成模块", 30);
        menuPrint("4、维修处理中心", 30);
        menuPrint("5、住宿管理中心", 30);
        menuPrint("0、退出登录", 30);
        menuPrint("DOWN", 30);
        slowPrint("请输入您的选择：", 30, -1);
        // cout << "\n---- 管理员菜单 ----\n";
        // cout << "1. 舍楼管理中心\n";
        // cout << "2. 用户管理中心\n";
        // cout << "3. 报表生成模块\n";
        // cout << "4. 维修处理中心\n";
        // cout << "5. 住宿管理中心\n";
        // cout << "0. 退出登录\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();

        switch (choice)
        {
            case 1:
                system("cls");
                manageDormitories(); // 管理宿舍楼
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                manageUsers(); // 管理用户
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                generateReports();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                userManager->handleRepairRequests(); // 处理维修请求
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                dormManageMenu();
                break;
            case 0:
                slowPrint("正在退出登录...", 30, -1);
            //cout << "正在退出登录...\n";
                Sleep(1000);
                system("cls");
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理用户
void manageUsers()
{
    string ID;

    while (true)
    {
        slowPrint("●管理用户●", 40, 0);
        menuPrint("UP", 40);
        menuPrint("1、添加用户", 40);
        menuPrint("2、删除用户", 40);
        menuPrint("3、通过学号查看用户信息", 40);
        menuPrint("4、通过姓名查看用户信息", 40);
        menuPrint("5、查看全部用户信息", 40);
        menuPrint("6、修改用户密码", 40);
        menuPrint("0、返回上一级", 40);
        menuPrint("DOWN", 40);
        slowPrint("请输入您的选择：", 40, -1);
        // cout << "\n---- 管理用户 ----\n";
        // cout << "1. 添加用户\n";
        // cout << "2. 删除用户\n";
        // cout << "3. 通过学号查看用户信息\n";
        // cout << "4. 通过姓名查看用户信息\n";
        // cout << "5. 查看全部用户信息\n";
        // cout << "6. 修改用户密码\n";
        // cout << "0. 返回上一级\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();

        switch (choice)
        {
            case 1:
                system("cls");
                slowPrint("当前操作：添加用户\n", 100, -1);
                userManager->addUser();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                slowPrint("当前操作：删除用户\n", 100, -1);
                cin.ignore();
                ID = userManager->get_ID();
                if (ID == "exit") break;
                userManager->deleteUser(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                slowPrint("当前操作：通过学号查看用户信息\n", 100, -1);
                cin.ignore();
                ID = userManager->get_ID();
                if (ID == "exit") break;
                userManager->checkUserInfo(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                slowPrint("当前操作：通过姓名查看用户信息\n", 100, -1);
                cin.ignore();
                cout << "请输入查询的名字（支持模糊查询）：" << endl;
                getline(cin, ID);
                if (ID == "exit") break;
                userManager->checkUserInfoByName(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                loading("正在查询中", 50, 10);
                slowPrint("查询完成", 50, 0);
                Sleep(500);
                system("cls");
                userManager->checkUserInfoALL();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 6:
                system("cls");
                slowPrint("当前操作：修改用户密码\n", 100, -1);
                cin.ignore();
                ID = userManager->get_ID();
                if (ID == "exit") break;
                userManager->userPasswordChange(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 0:
                system("cls");
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
    while (true)
    {
        slowPrint("●住宿管理●", 30, 0);
        menuPrint("UP", 30);
        menuPrint("1、安排住宿", 30);
        menuPrint("2、安排退宿", 30);
        menuPrint("3、处理学生申请", 30);
        menuPrint("4、查看住宿记录", 30);
        menuPrint("5、查看所有未入住学生", 30);
        menuPrint("0、返回上一级", 30);
        menuPrint("DOWN", 30);
        slowPrint("请输入您的选择：", 30, -1);
        // cout << "\n---- 住宿管理 ----\n";
        // cout << "1. 安排住宿\n";
        // cout << "2. 安排退宿\n";
        // cout << "3. 处理学生申请\n";
        // cout << "4. 查看住宿记录\n";
        // cout << "0. 返回上一级\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();
        switch (choice)
        {
            case 1:
                system("cls");
                slowPrint("当前操作：安排住宿\n", 100, -1);
                cin.ignore();
                while (true)
                {
                    ID = userManager->get_ID();
                    // 检查是否已经入住
                    if (userManager->isStudentCheckedIn(ID))
                    {
                        cout << "该学生已入住，请重新选择其他学生。\n";
                        continue;
                    }
                    break;
                }
                if (ID == "exit") break;
                userManager->arrangeAccommodation(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                slowPrint("当前操作：安排退宿\n", 100, -1);
                cin.ignore();
                while (true)
                {
                    ID = userManager->get_ID();
                    // 检查是否已经入住
                    if (!userManager->isStudentCheckedIn(ID))
                    {
                        cout << "该学生未入住，请重新选择其他学生。\n";
                        continue;
                    }
                    break;
                }
                if (ID == "exit") break;
                userManager->arrangeCheckOut(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                slowPrint("当前操作：处理学生申请\n", 100, -1);
                userManager->dealAccommodationRequests();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                slowPrint("当前操作：查看住宿记录\n", 100, -1);
                cin.ignore();
                cout << "请输入您想查询的学生学号（若不输入则查询所有记录）" << endl;
                getline(cin, ID);
                userManager->viewCheckInOutRecords(ID);
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                slowPrint("当前操作：查看未入住的学生\n", 100, -1);
                userManager->checkUserNotCheckedIn();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 0:
                system("cls");
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 生成报表
void generateReports()
{
    while (true)
    {
        slowPrint("●生成报表●", 40, 0);
        menuPrint("UP", 40);
        menuPrint("1、生成宿舍使用情况报表", 40);
        menuPrint("2、生成入住率报表", 40);
        menuPrint("3、返回上一级", 40);
        menuPrint("DOWN", 40);
        slowPrint("请输入您的选择：", 40, -1);
        // cout << "\n---- 生成报表 ----\n";
        // cout << "1. 生成宿舍使用情况报表\n";
        // cout << "2. 生成入住率报表\n";
        // cout << "3. 返回上一级\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();
        switch (choice)
        {
            case 1:
                userManager->viewAllDormitories();
                break;
            case 2:
                userManager->generateAccommodationRateReport();
                break;
            case 3:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理宿舍楼
void manageDormitories()
{
    while (true)
    {
        slowPrint("●管理宿舍楼●", 30, 0);
        menuPrint("UP", 30);
        menuPrint("1、添加宿舍楼", 30);
        menuPrint("2、删除宿舍楼", 30);
        menuPrint("3、查看宿舍楼信息", 30);
        menuPrint("4、修改宿舍楼信息", 30);
        menuPrint("5、房间管理", 30);
        menuPrint("0、返回上一级", 30);
        menuPrint("DOWN", 30);
        slowPrint("请输入您的选择：", 30, -1);
        // cout << "\n---- 管理宿舍楼 ----\n";
        // cout << "1. 添加宿舍楼\n";
        // cout << "2. 删除宿舍楼\n";
        // cout << "3. 查看宿舍楼信息\n";
        // cout << "4. 房间管理\n";
        // cout << "0. 返回上一级\n";
        // cout << "请输入你的选择: ";
        int choice = getChoice();

        switch (choice)
        {
            case 1:
                system("cls");
                slowPrint("当前操作：添加宿舍楼\n", 100, -1);
                userManager->addDormitory();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                slowPrint("当前操作：删除宿舍楼\n", 100, -1);
                userManager->deleteDormitory();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
            //deleteDormitory();
                break;
            case 3:
                system("cls");
                loading("正在加载中", 50, 40);
                slowPrint("加载完成", 50, 0);
                Sleep(500);
                system("cls");
                userManager->viewAllDormitories();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                slowPrint("当前操作：修改宿舍楼信息\n", 100, -1);
                userManager->modifyDormitoryInfo();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                slowPrint("当前操作：房间管理\n", 100, -1);
                userManager->manageRooms();
                slowPrint("请按任意键继续", 30, -1);
                getch();
                system("cls");
                break;
            case 0:
                system("cls");
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}
