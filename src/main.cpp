#include <iostream>
#include "Person.h"
#include "User.h"
#include <windows.h>
using namespace std;


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    // 创建一个管理员用户
    User admin("admin001", "Alice", "admin123", "alice@example.com", true);
    admin.insertUser();

    // 创建一个学生用户
    User student("stu123", "Bob", "student123", "bob@example.com", false);
    student.insertUser();

    // 测试输出用户信息
    cout << "用户ID: " << admin.getUserID() << ", 姓名: " << admin.getName() << ", 是否管理员: " << (
        admin.getIsAdmin() ? "是" : "否") << endl;
    cout << "联系方式: " << admin.getContactInfo() << endl;

    cout << "用户ID: " << student.getUserID() << ", 姓名: " << student.getName() << ", 是否管理员: " << (
        student.getIsAdmin() ? "是" : "否") << endl;
    cout << "联系方式: " << student.getContactInfo() << endl;

    // 测试密码验证
    string inputPassword;
    cout << "请输入管理员的密码: ";
    cin >> inputPassword;
    if (admin.checkPassword(inputPassword))
    {
        cout << "管理员密码正确！" << endl;
    } else
    {
        cout << "管理员密码错误！" << endl;
    }

    cout << "请输入学生的密码: ";
    cin >> inputPassword;
    if (student.checkPassword(inputPassword))
    {
        cout << "学生密码正确！" << endl;
    } else
    {
        cout << "学生密码错误！" << endl;
    }

    // 测试修改联系方式
    admin.setContactInfo("alice@newdomain.com");
    student.setContactInfo("bob@newdomain.com");

    cout << "更新后的管理员联系方式: " << admin.getContactInfo() << endl;
    cout << "更新后的学生联系方式: " << student.getContactInfo() << endl;

    return 0;
}
