#include <iostream>
#include <Database.h>
#include <windows.h>
#include <UserManager.h>
#include <iostream>
#include <string>
using namespace std;

UserManager *userManager = nullptr; // 只声明指针，初始化将在 main 函数中进行
// 函数声明
void showMainMenu();

void userLogin();

void studentRegister();

void studentMenu();

void adminMenu();

void manageDormitories();

void studentLoginMenu();

void manageUsers();

void generateReports();

void handleRepairRequests();

void viewDormitoryInfo();

void requestRoomChange();

void submitRepairRequest();

void adminLogin();

void studentLogin();

void viewNotifications();


// 主程序入口
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choice;
    userManager = new UserManager(); // 这里会自动连接数据库
    userManager->getAllUsers();


    while (true)
    {
        cout << "\n---- 主菜单 ----\n";
        cout << "1. 学生菜单\n";
        cout << "2. 管理员菜单\n";
        cout << "3. 退出\n";
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
            case 3:
                cout << "退出程序...\n";
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
        studentMenu(); // 登录成功后跳转到学生菜单
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
    userManager->registerUser(studentID, password, name, gender, contactInfo, 0, 0);
}

void adminMenu()
{
    int choice;
    while (true)
    {
        cout << "\n---- 管理员菜单 ----\n";
        cout << "1. 管理宿舍楼\n";
        cout << "2. 管理用户\n";
        cout << "3. 生成报表\n";
        cout << "4. 处理维修请求\n";
        cout << "5. 退出登录\n";
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
                cout << "正在退出登录...\n";
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

void studentMenu()
{
    int choice;
    while (true)
    {
        cout << "\n---- 学生菜单 ----\n";
        cout << "1. 查看宿舍楼和房间信息\n";
        cout << "2. 请求换房\n";
        cout << "3. 提交维修请求\n";
        cout << "4. 查看通知\n";
        cout << "5. 退出登录\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                viewDormitoryInfo(); // 查看宿舍楼和房间信息
                break;
            case 2:
                requestRoomChange(); // 请求换房
                break;
            case 3:
                submitRepairRequest(); // 提交维修请求
                break;
            case 4:
                viewNotifications(); // 查看通知
                break;
            case 5:
                cout << "正在退出登录...\n";
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员管理宿舍楼
void manageDormitories()
{
    int choice;
    while (true)
    {
        cout << "\n---- 管理宿舍楼 ----\n";
        cout << "1. 添加宿舍楼\n";
        cout << "2. 删除宿舍楼\n";
        cout << "3. 查看宿舍楼信息\n";
        cout << "4. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // TODO: 添加宿舍楼
                cout << "添加宿舍楼 - 功能开发中。\n";
                break;
            case 2:
                // TODO: 删除宿舍楼
                cout << "删除宿舍楼 - 功能开发中。\n";
                break;
            case 3:
                // TODO: 查看宿舍楼信息
                cout << "查看宿舍楼信息 - 功能开发中。\n";
                break;
            case 4:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 管理员管理用户
void manageUsers()
{
    int choice;
    while (true)
    {
        cout << "\n---- 管理用户 ----\n";
        cout << "1. 添加用户\n";
        cout << "2. 删除用户\n";
        cout << "3. 查看用户信息\n";
        cout << "4. 返回上一级\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // TODO: 添加用户
                cout << "添加用户 - 功能开发中。\n";
                break;
            case 2:
                // TODO: 删除用户
                cout << "删除用户 - 功能开发中。\n";
                break;
            case 3:
                // TODO: 查看用户信息
                cout << "查看用户信息 - 功能开发中。\n";
                break;
            case 4:
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

// 学生查看宿舍信息
void viewDormitoryInfo()
{
    cout << "查看宿舍楼和房间信息 - 功能开发中。\n";
}

// 学生请求换房
void requestRoomChange()
{
    cout << "请求换房 - 功能开发中。\n";
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
