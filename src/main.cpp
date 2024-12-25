#include <iostream>
#include <windows.h>
#include <UserManager.h>
#include <limits>
#include <string>
using namespace std;

UserManager *userManager = nullptr; // 只声明指针，初始化将在 main 函数中进行
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

void manageUsers();

void checkUserInfo(const string &userID);

void generateReports();

void handleRepairRequests();

void viewDormitoryInfo(const string &stuID);

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
    userManager = new UserManager(); // 自动连接数据库
    // userManager->getAllUsers();
    //adminMenu();
    //userManager->arrangeAccommodation();
    //userManager->arrangeCheckOut();

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
    cout << "3. 退出\n";
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
        case 3:
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
        int str_len = studentID.size();
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

void studentMenu(const string &stuID)
{
    int choice;
    while (true)
    {
        cout << "\n---- 学生菜单 ----\n";
        cout << "1. 查看宿舍楼和房间信息\n";
        cout << "2. 请求换房\n";
        cout << "3. 提交维修请求\n";
        cout << "4. 查看通知\n";
        cout << "5. 修改密码\n";
        cout << "0. 退出登录\n";
        cout << "请输入你的选择: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                viewDormitoryInfo(stuID); // 查看宿舍楼和房间信息
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
                userManager->UserPasswordChange(stuID);
                break;
            case 0:
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
                addDormitory();
                break;
            case 2:
                deleteDormitory();
                break;
            case 3:
                viewDormitories();
                break;
            case 4:
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
                   COUNT(r.roomID) AS roomCount,
                   SUM(CASE WHEN r.occupied = r.capacity THEN 1 ELSE 0 END) AS fullRoomCount
            FROM dormitories d
            LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
            GROUP BY d.dormitoryID;
        )";

    // 执行SQL语句
    userManager->Query(sql);
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
        cout << "3. 查看用户信息\n";
        cout << "4. 安排住宿\n";
        cout << "5. 安排退宿\n";
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
                        cin >> userID;
                        int str_len = userID.size();
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
                        cout << "请输入第" << i << "位用户的性别：";
                        cin >> gender;
                        string contactInfo;
                        cout << "请输入第" << i << "位用户的联系方式：";
                        cin >> contactInfo;
                        userManager->registerUser(userID, password, name, gender, contactInfo, false, false);
                    }
                }
                break;
            case 2:
                // TODO: 删除用户
                cout << "删除用户 - 功能开发中。\n";
                break;
            case 3:
                cout << "请输入学号:\n";
                cin.ignore();
                getline(cin, ID);
                checkUserInfo(ID);

                break;
            case 4:
                cin.ignore();
                userManager->arrangeAccommodation();
                break;
            case 5:
                cin.ignore();
                while (true)
                {
                    // 输入学号
                    cout << "请输入学号(输入exit可返回)：";
                    getline(cin, ID);
                    if (ID == "exit")
                    {
                        return;
                    }
                    // 检查学号是否存在
                    if (!userManager->IDExists(ID))
                    {
                        cout << "学号不存在，请重新输入。\n";
                        continue;
                    }
                    // 检查是否已入住
                    if (!userManager->IsStudentCheckedIn(ID))
                    {
                        // 学生未入住
                        cout << "该学生尚未入住，无法执行退宿操作。\n";
                        continue;
                    }

                    break; // 如果学号存在且已入住，则退出循环，继续后续操作
                }
                userManager->arrangeCheckOut(ID);
                break;
            case 0:
                return;
            default:
                cout << "无效选择，请重新输入。\n";
        }
    }
}

// 查看用户信息
void checkUserInfo(const string &userID)
{
    if (!userManager->studentExistsByID(userID))
    {
        cout << "用户不存在\n";
    } else
    {
        bool flag = userManager->IsStudentCheckedIn(userID); //查询的同学是否已经入住
        if (flag == false)
        {
            string sql = "SELECT "
                         "    u.userID AS 学号,           -- 学生学号\n"
                         "    u.name AS 姓名,           -- 学生名称\n"
                         "    u.gender AS 性别,           -- 学生性别\n"
                         "    u.password AS 密码,           -- 学生密码\n"
                         "    u.contactInfo AS 联系方式           -- 学生联系方式\n"
                         "FROM "
                         "    users u \n"
                         "WHERE "
                         "    u.userID = '" + userID + "';"; // 使用学生ID作为参数传递
            // 调用Query方法，执行SQL查询
            userManager->Query(sql);
            cout << "\n该学生暂未入住，建议尽快安排入住\n";
        } else
        {
            string sql = "SELECT "
                         "    u.userID AS 学号,           -- 学生学号\n"
                         "    u.name AS 姓名,           -- 学生名称\n"
                         "    u.gender AS 性别,           -- 学生性别\n"
                         "    u.password AS 密码,           -- 学生密码\n"
                         "    u.contactInfo AS 联系方式,           -- 学生联系方式\n"
                         "    d.name AS 宿舍楼,           -- 宿舍楼名称\n"
                         "    r.roomNumber AS 房间号        -- 房间号\n"
                         "FROM "
                         "    student_rooms sr\n"
                         "JOIN "
                         "    rooms r ON sr.roomID = r.roomID   -- 连接房间表\n"
                         "JOIN "
                         "    dormitories d ON r.dormitoryID = d.dormitoryID -- 连接宿舍楼表\n"
                         "JOIN "
                         "    users u ON sr.studentID = u.userID -- 连接学生表\n"
                         "WHERE "
                         "    u.userID = '" + userID + "';"; // 使用学生ID作为参数传递
            // 调用Query方法，执行SQL查询
            userManager->Query(sql);
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
void viewDormitoryInfo(const string &stuID)
{
    string sql = "SELECT "
                 "    d.name AS dormitory_name,           -- 宿舍楼名称\n"
                 "    r.roomNumber AS room_number,        -- 房间号\n"
                 "    r.capacity AS room_capacity,       -- 房间容量\n"
                 "    r.occupied AS room_occupied,       -- 已入住人数\n"
                 "    r.repair_status AS repair_status   -- 维修状态\n"
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

    userManager->Query(sql);
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
