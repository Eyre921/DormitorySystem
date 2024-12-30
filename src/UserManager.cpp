#include "UserManager.h"

#include <conio.h>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>

#include "specialPrint.h"
using namespace std;


// 构造函数，自动连接数据库
UserManager::UserManager() : db("dormitory.db")
{
    db.updateRoomStatus();
    // cout << "数据库链接成功" << endl;
    // cout << "数据库状态更新成功" << endl;

    // 在这里，可以进行数据库的初始化（例如创建表等操作）
    // if (!db.execute(
    //     "CREATE TABLE IF NOT EXISTS users (userID TEXT PRIMARY KEY, name TEXT, gender TEXT, password TEXT, contactInfo TEXT, isCheckedIn INTEGER DEFAULT 0, isAdmin INTEGER DEFAULT 0);"))
    // {
    //     cout << "数据库创建失败！\n";
    //     exit(1); // 如果数据库创建失败，退出程序
    // }
}

// 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 // 数据库功能 //

// 查询并打印
void UserManager::query(const string &SQL)
{
    db.query(SQL);
}

// 执行
void UserManager::execute(const string &SQL)
{
    db.execute(SQL);
}

// 查询但不打印
bool UserManager::queryExists(const string &SQL)
{
    return db.queryExists(SQL);
}


// 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 // 通用功能 //

// 一键获取所有用户信息
void UserManager::getAllUsers()
{
    db.query("SELECT * FROM users;");
}

// 获取并返回ID
string UserManager::get_ID()
{
    string studentID;
    while (true)
    {
        // 输入学号
        cout << "请输入学号(输入exit可返回)：";
        getline(cin, studentID);
        if (studentID == "exit")
        {
            return studentID;
        }
        // 检查学号是否存在
        string checkStudentQuery = "SELECT 1 FROM users WHERE userID = '" + studentID + "' AND isAdmin = 0;";
        if (!queryExists(checkStudentQuery))
        {
            // 学号不存在
            cout << "学号不存在，请重新输入。\n";
            continue;
        }

        return studentID; // 如果学号存在且未入住，则退出循环，继续后续操作
    }
}

// ID是否存在（包括管理员）
bool UserManager::IDExists(const string &studentID)
{
    string checkStudentQuery = "SELECT 1 FROM users WHERE userID = '" + studentID +
                               "' AND isAdmin = 0;";
    return queryExists(checkStudentQuery);
}

// 宿舍是否存在
bool UserManager::dormitoryExistsByName(const string &dormitoryName)
{
    // 模拟查询语句
    string sql = "SELECT * FROM dormitories WHERE name = '" + dormitoryName + "';";

    // 调用查询函数来检查数据库中是否已有该宿舍楼名称
    if (db.queryExists(sql))
    {
        return true; // 如果返回 true，表示该宿舍楼名称已存在
    } else
    {
        return false; // 如果没有找到，表示该宿舍楼名称不存在
    }
}

// 学生ID是否存在（不包括管理员）
bool UserManager::studentExistsByID(const string &ID)
{
    // 模拟查询语句
    string sql = "SELECT * FROM users WHERE userID = '" + ID + "';";
    return db.queryExists(sql);
}

int UserManager::getDormitoryIDByName(const string &dormitoryName)
{
    string queryDormitory = "SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "'";
    // 执行查询
    db.queryExists(queryDormitory);
    // 检查查询结果
    if (sqlite3_step(db.stmt) != SQLITE_ROW)
    {
        cout << "宿舍楼id获取失败。\n";
        return 0; // 终止函数，避免继续执行
    }
    // 获取楼栋的ID
    string dormitoryID = db.getQueryResult(0);
    return stoi(dormitoryID);
}

// 选择保护函数
int UserManager::getChoice()
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

// 用户登录
bool UserManager::loginUser(const string &userID, const string &password, const string &isAdmin)
{
    string sql = "SELECT * FROM users WHERE userID = '" + userID + "' AND password = '" + password + "' AND isAdmin = '"
                 + isAdmin + "';";

    if (db.queryExists(sql))
    {
        cout << "登录成功！";
        return true; // 登录成功
    }
    cout << "登录失败！";
    return false; // 登录失败
}

// 用户注册
bool UserManager::registerUser(const string &userID, const string &password, const string &name, const string &gender,
                               const string &contactInfo, bool isCheckedIn, bool isAdmin)
{
    // 构造插入语句
    string sql = "INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) "
                 "VALUES ('" + userID + "', '" + name + "', '" + gender + "', '" + password + "', '" + contactInfo +
                 "', " + to_string(isCheckedIn) + ", " + to_string(isAdmin) + ");";

    // 尝试执行插入操作
    if (db.execute(sql))
    {
        cout << "用户注册成功！\n";
        return true;
    } else
    {
        cout << "用户注册失败，可能是账号已存在。\n";
        return false; // 插入失败
    }
}

// 修改密码
bool UserManager::userPasswordChange(const string &userID)
{
    string newPassword;
    cout << "请输入新密码:";
    cin >> newPassword;
    // 构造插入语句
    string sql = "UPDATE users SET password = '" + newPassword + "' WHERE userID = " + userID + ";";
    // 尝试执行插入操作
    if (db.execute(sql))
    {
        cout << "密码修改成功！\n";
        return true;
    } else
    {
        cout << "密码修改失败……\n";
        return false; // 插入失败
    }
}

// 是否入住
bool UserManager::isStudentCheckedIn(const string &studentID)
{
    string checkCheckedInQuery = "SELECT isCheckedIn FROM users WHERE userID = '" + studentID +
                                 "' AND isCheckedIn = 1;";

    return queryExists(checkCheckedInQuery);
}

// 选择有效的宿舍（通过引用修改）
void UserManager::selectValidRoom(const string &studentID, string &dormitoryName, string &roomChoice)
{
    string free_dorm =
            "SELECT d.name AS 宿舍楼, d.sex AS 类型, d.position AS 位置, "
            "r.roomNumber AS 房间名, r.capacity AS 容量, r.occupied AS 现有人数 "
            "FROM dormitories d "
            "JOIN rooms r ON d.dormitoryID = r.dormitoryID "
            "JOIN users u ON u.gender = d.sex " // 确保宿舍楼性别与用户性别匹配
            "WHERE r.occupied < r.capacity "
            "AND r.repair_status = '正常' "
            "AND u.userID = '" + studentID + "' " // 使用当前学生的 studentID
            "ORDER BY d.name, r.roomNumber;";


    query(free_dorm);

    while (true)
    {
        cout << "请输入宿舍楼名称：" << endl;
        getline(cin, dormitoryName);
        if (dormitoryName == "exit")
        {
            return;
        }
        string queryAvailableRooms = "SELECT r.roomID, r.roomNumber, r.capacity, r.occupied "
                                     "FROM rooms r "
                                     "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                                     "JOIN users u ON u.gender = d.sex " // 确保宿舍楼性别与用户性别匹配
                                     "WHERE d.name = '" + dormitoryName + "' "
                                     "AND r.occupied < r.capacity "
                                     "AND u.userID = '" + studentID + "';"; // 使用学生ID进行匹配

        // 使用 QueryExists 来检查宿舍楼是否存在并且有空房间
        if (!queryExists(queryAvailableRooms))
        {
            cout << "宿舍楼名称不正确或没有空房间，请重新输入。\n";
            continue;
        }
        break;
    }

    // 查询宿舍楼下所有空房间号（已入住为0）

    string sql = "SELECT r.roomNumber AS 房间号, r.capacity AS 房间容量, r.occupied AS 已入住人数 "
                 "FROM rooms r "
                 "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                 "WHERE d.name = '" + dormitoryName + "' "
                 "AND r.occupied < r.capacity;";

    // 使用 Query 查询空闲房间
    query(sql);


    while (true)
    {
        cout << "请输入您选择的房间号：";
        getline(cin, roomChoice);
        if (roomChoice == "exit")
        {
            return;
        }


        string queryRoomExists = "SELECT 1 FROM rooms r "
                                 "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                                 "WHERE d.name = '" + dormitoryName + "' "
                                 "AND r.roomNumber = '" + roomChoice + "' "
                                 "AND r.occupied < r.capacity;";

        // 使用 QueryExists 来检查房间号是否存在并且可用
        if (!queryExists(queryRoomExists))
        {
            cout << "房间号不正确或已满，请重新输入。\n";
            continue;; // 如果房间无效，返回并重新开始
        }
        break;
    }
}

// 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 // 管理员菜单 //

// 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 // 管理宿舍楼 //
// 添加宿舍楼
void UserManager::addDormitory()
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
            if (dormitoryExistsByName(dormitoryName))
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
    db.execute(sql);

    // 获取新插入的宿舍楼ID（这里假设为1）
    int dormitoryID = getDormitoryIDByName(dormitoryName);

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
        execute(roomSql);
    }

    cout << "宿舍楼和房间信息添加成功！\n";
}

// 删除宿舍楼
void UserManager::deleteDormitory()
{
    string dormitoryName;
    cin.ignore(); // 清除输入缓存
    viewAllDormitories(); // 显示所有楼栋信息

    // 提示管理员输入楼栋名称
    cout << "请输入要删除的宿舍楼名称: " << endl;
    getline(cin, dormitoryName);

    // 查询楼栋是否存在
    string queryDormitory = "SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "'";

    // 执行查询
    db.queryExists(queryDormitory);

    // 检查查询结果
    if (sqlite3_step(db.stmt) != SQLITE_ROW)
    {
        cout << "未找到该宿舍楼。\n";
        return; // 终止函数，避免继续执行
    }

    // 获取楼栋的ID
    string dormitoryID = db.getQueryResult(0);

    // 查询该楼栋下所有的房间ID（将房间ID存储在一个容器中）
    unordered_set<string> roomIDs; // 用于存储房间ID
    string queryRooms = "SELECT r.roomID "
                        "FROM rooms r "
                        "WHERE r.dormitoryID = '" + dormitoryID + "'"; // 拼接 dormitoryID

    db.queryExists(queryRooms); // 执行查询房间ID

    // 遍历查询结果，将房间ID存入集合
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        string roomID = db.getQueryResult(0); // 获取房间ID
        roomIDs.insert(roomID); // 将房间ID插入到集合中
    }
    bool hasStudentLiveIn = false;
    // 如果没有房间，返回
    if (roomIDs.empty())
    {
        cout << "该楼栋没有房间。\n";
    } else
    {
        // 4. 遍历房间ID集合，查询每个房间的居住情况
        for (const string &roomID: roomIDs)
        {
            // 查询该房间的详细信息
            string queryRoomDetails = "SELECT r.roomNumber, r.capacity, r.occupied "
                                      "FROM rooms r "
                                      "WHERE r.roomID = '" + roomID + "'";

            db.queryExists(queryRoomDetails);

            string roomNumber;
            int capacity = 0;
            int occupied = 0;

            if (sqlite3_step(db.stmt) == SQLITE_ROW)
            {
                roomNumber = db.getQueryResult(0); // 获取房间号
                capacity = stoi(db.getQueryResult(1)); // 获取房间容量
                occupied = stoi(db.getQueryResult(2)); // 获取已入住人数
            }

            // 打印房间的居住情况
            cout << "房间号: " << roomNumber << ", 容量: " << capacity << ", 已入住: " << occupied << endl;

            // 如果房间内有学生入住，则调用 ViewStudentsInRoom 打印学生信息
            if (occupied > 0)
            {
                hasStudentLiveIn = true;
                viewStudentsInRoom(dormitoryName, roomNumber); // 打印住在该房间的学生信息
            }
        }
    }
    if (hasStudentLiveIn)
    {
        cout << "本栋有学生入住，请先处理他们的退宿" << endl;
        return;
    }
    // 提示管理员是否删除该楼栋
    string confirmDelete;
    cout << "确认删除宿舍楼 " << dormitoryName << " 吗？(yes/no): ";
    getline(cin, confirmDelete);

    if (confirmDelete == "yes")
    {
        // 删除该楼栋下的所有房间
        string deleteRoomsQuery = "DELETE FROM rooms WHERE dormitoryID = ?";
        db.executeWithParams(deleteRoomsQuery, {dormitoryID});

        // 删除楼栋
        string deleteDormitoryQuery = "DELETE FROM dormitories WHERE dormitoryID = ?";
        db.executeWithParams(deleteDormitoryQuery, {dormitoryID});

        cout << "宿舍楼 " << dormitoryName << " 已删除。\n";
    } else
    {
        cout << "取消删除宿舍楼 " << dormitoryName << ".\n";
    }
}

/*
void deleteDormitory_old()
{
    cin.ignore();
    string dormitoryName;
    viewDormitories();
    // 检查宿舍楼名称输入是否存在
    cout << "请输入要删除的宿舍楼名称：";
    while (true)
    {
        getline(cin, dormitoryName); // 使用getline()读取宿舍楼名称
        if (dormitoryName == "exit ") return;
        if (!dormitoryName.empty())
        {
            // 检查宿舍楼是否存在
            if (dormitoryExistsByName(dormitoryName))
            {
                break; // 存在，跳出循环
            } else
            {
                cout << "宿舍楼名称不存在，请重新输入有效的名称：";
            }
        } else
        {
            cout << "宿舍楼名称不能为空，请输入：";
        }
    }

    // 检查宿舍楼是否有房间有学生入住
    string checkRoomsSql = R"(
        SELECT 1
        FROM rooms r
        JOIN dormitories d ON r.dormitoryID = d.dormitoryID
        WHERE d.name = ')" + dormitoryName + "' AND r.occupied > 0 LIMIT 1;)";
    Query(checkRoomsSql);
    // 调用 UserManager 的方法，检查是否有学生入住
    if (hasStudentsInDormitoryRooms(checkRoomsSql))
    {
        cout << "该宿舍楼下有房间已被学生入住。请先处理这些学生的退宿，直到房间为空。\n";
        return; // 如果有学生入住，返回，不删除宿舍楼
    }

    // 构造SQL语句来删除宿舍楼
    string sql = "DELETE FROM dormitories WHERE name = '" + dormitoryName + "';";

    // 执行SQL语句
    execute(sql);

    cout << "宿舍楼 '" << dormitoryName << "' 删除成功。\n";
}
bool UserManager::hasStudentsInDormitoryRooms(const string &checkRoomsSql)
{
    return db.hasStudentsInDormitoryRooms(checkRoomsSql);
}
*/

// 查看所有宿舍楼信息
void UserManager::viewAllDormitories()
{
    // 构造SQL语句
    string sql = R"(
            SELECT d.name AS 宿舍楼,
                   d.sex AS 类型,
                   d.position AS 位置,
                   COUNT(r.roomID) AS 房间数,
                   SUM(r.capacity) AS 总容量,
                   SUM(r.occupied) AS 居住人数,
                   ROUND(SUM(r.occupied) * 100.0 / SUM(r.capacity), 2) AS 占用比率
            FROM dormitories d
            LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
            GROUP BY d.dormitoryID;
        )";

    // 执行SQL语句
    db.query(sql);
}

// 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 // 房间管理 //

// 查看选定宿舍楼的所有房间信息和入住学生
void UserManager::viewAllRooms(const string &dormitoryName)
{
    string queryDormitory = "SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "'";
    // 执行查询
    db.queryExists(queryDormitory);
    if (sqlite3_step(db.stmt) != SQLITE_ROW)
    {
        cout << "未找到该宿舍楼。\n";
        return; // 终止函数，避免继续执行
    }
    // 获取楼栋的ID
    string dormitoryID = db.getQueryResult(0);
    // 查询该楼栋下所有的房间ID（将房间ID存储在一个容器中）
    unordered_set<string> roomIDs; // 用于存储房间ID
    string queryRooms = "SELECT r.roomID "
                        "FROM rooms r "
                        "WHERE r.dormitoryID = '" + dormitoryID + "'"; // 拼接 dormitoryID

    db.queryExists(queryRooms); // 执行查询房间ID

    // 遍历查询结果，将房间ID存入集合
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        string roomID = db.getQueryResult(0); // 获取房间ID
        roomIDs.insert(roomID); // 将房间ID插入到集合中
    }

    // 如果没有房间，返回
    if (roomIDs.empty())
    {
        cout << "该楼栋没有房间。\n";
        return;
    } else
    {
        // 4. 遍历房间ID集合，查询每个房间的居住情况
        for (const string &roomID: roomIDs)
        {
            // 查询该房间的详细信息
            string queryRoomDetails = "SELECT r.roomNumber, r.capacity, r.occupied "
                                      "FROM rooms r "
                                      "WHERE r.roomID = '" + roomID + "'";

            db.queryExists(queryRoomDetails);

            string roomNumber;
            int capacity = 0;
            int occupied = 0;

            if (sqlite3_step(db.stmt) == SQLITE_ROW)
            {
                roomNumber = db.getQueryResult(0); // 获取房间号
                capacity = stoi(db.getQueryResult(1)); // 获取房间容量
                occupied = stoi(db.getQueryResult(2)); // 获取已入住人数
            }
            // 打印房间的居住情况
            cout << "房间号: " << roomNumber << ", 容量: " << capacity << ", 已入住: " << occupied << endl;
        }
    }
}

// 房间管理菜单
void UserManager::manageRooms()
{
    string dormitoryName;
    cin.ignore(); // 清除输入缓存
    viewAllDormitories(); // 显示所有楼栋信息

    // 提示管理员输入楼栋名称
    cout << "请输入宿舍楼名称: " << endl;
    getline(cin, dormitoryName);

    // 查询楼栋是否存在
    string queryDormitory = "SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "'";

    // 执行查询
    db.queryExists(queryDormitory);

    // 检查查询结果
    if (sqlite3_step(db.stmt) != SQLITE_ROW)
    {
        cout << "未找到该宿舍楼。\n";
        return; // 终止函数，避免继续执行
    }

    // 获取楼栋的ID
    string dormitoryID = db.getQueryResult(0);

    // 查询该楼栋下所有的房间ID（将房间ID存储在一个容器中）
    unordered_map<string, string> rooms; // 用于存储房间名字-ID
    string queryRooms = "SELECT r.roomNumber,r.roomID "
                        "FROM rooms r "
                        "WHERE r.dormitoryID = '" + dormitoryID + "'"; // 拼接 dormitoryID

    db.queryExists(queryRooms); // 执行查询房间ID

    // 遍历查询结果，将房间ID存入集合
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        string roomNumber = db.getQueryResult(0); // 获取房间名
        string roomID = db.getQueryResult(1); // 获取房间ID
        rooms.insert({roomNumber, roomID}); // 将房间ID插入到集合中
    }

    // 如果没有房间，返回
    if (rooms.empty())
    {
        cout << "该楼栋没有房间。\n";
    } else
    {
        viewAllRooms(dormitoryName);
    }

    string selectedRoomNumber;


    cout << "请输入选择的房间号" << endl;
    getline(cin, selectedRoomNumber);
    auto it = rooms.find(selectedRoomNumber);
    if (it == rooms.end())
    {
        cout << "未找到该房间。" << endl;
        return;
    } else
    {
        string selectedRoomID = it->second;
        string queryRoomDetails = "SELECT r.capacity, r.occupied "
                                  "FROM rooms r "
                                  "WHERE r.roomID = '" + selectedRoomID + "'";

        db.queryExists(queryRoomDetails);

        int capacity = 0;
        int occupied = 0;

        if (sqlite3_step(db.stmt) == SQLITE_ROW)
        {
            capacity = stoi(db.getQueryResult(0)); // 获取房间容量
            occupied = stoi(db.getQueryResult(1)); // 获取已入住人数
        }

        while (true)
        {
            SlowPrint("●管理房间●", 30, 0);
            MenuPrint("UP", 30);
            MenuPrint("1、查看入住信息", 30);
            MenuPrint("2、删除房间", 30);
            MenuPrint("3、修改房间信息", 30);
            MenuPrint("0、返回上一级", 30);
            MenuPrint("DOWN", 30);
            SlowPrint("请输入您的选择：", 30, -1);
            // cout << "\n---- 管理房间 ----\n";
            // cout << "1. 查看入住信息\n";
            // cout << "2. 删除房间\n";
            // cout << "3. 修改房间信息\n";
            // cout << "0. 返回上一级\n";
            // cout << "请输入你的选择: ";
            int choice = getChoice();

            switch (choice)
            {
                case 1:
                    viewStudentsInRoom(dormitoryName, selectedRoomNumber);
                    break;
                case 2:
                    if (occupied > 0)
                    {
                        cout << "该房间还有学生入住，请处理" << endl;
                        viewStudentsInRoom(dormitoryName, selectedRoomNumber);
                    } else
                    {
                        deleteRoom(selectedRoomID);
                        cout << "删除" << selectedRoomNumber << "成功" << endl;
                        return;
                    }
                    break;
                case 3:
                    modifyRoomInfo(selectedRoomID, capacity);
                    break;
                case 0:
                    return;
                default:
                    cout << "无效选择，请重新输入。\n";
            }
        }
    }
}

// 1. 查看入住信息
void UserManager::viewStudentsInRoom(const string &dormitoryName, const string &roomNumber)
{
    // 拼接查询语句，获取该房间中的所有学生姓名和ID
    string sql = "SELECT u.name, u.userID "
                 "FROM users u "
                 "JOIN student_rooms sr ON u.userID = sr.studentID "
                 "JOIN rooms r ON sr.roomID = r.roomID "
                 "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                 "WHERE d.name = '" + dormitoryName + "' AND r.roomNumber = '" + roomNumber + "';";

    // 存储学生的姓名和ID
    vector<pair<string, string> > students; // 每个元素是学生姓名和ID的组合

    // 执行查询
    db.queryExists(sql);

    // 遍历查询结果并将学生姓名和ID存储到数组中
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        string studentName = db.getQueryResult(0); // 获取学生姓名
        string studentID = db.getQueryResult(1); // 获取学生ID
        students.emplace_back(studentName, studentID); // 存储学生姓名和ID
    }

    // 如果没有找到任何学生，输出提示信息
    if (students.empty())
    {
        cout << "该房间没有学生入住。\n";
    } else
    {
        // 打印学生信息：姓名和ID
        cout << "\t学生姓名(学号): ";
        for (size_t i = 0; i < students.size(); ++i)
        {
            // 每个学生的姓名和ID格式： 姓名（ID）
            cout << students[i].first << "（" << students[i].second << "）";
            if (i < students.size() - 1)
            {
                cout << " | "; // 如果不是最后一个学生，加上分隔符 "|"
            }
        }
        cout << endl;
    }
}

// 2. 删除房间
void UserManager::deleteRoom(const string &selectedRoomID)
{
    string deleteRoomsQuery = "DELETE FROM rooms WHERE roomID = ?";
    db.executeWithParams(deleteRoomsQuery, {selectedRoomID});
}

// 3. 修改房间信息
void UserManager::modifyRoomInfo(const string &selectedRoomID, const int capacity)
{
    // 提供用户选择

    string newRoomNumber;
    int newCapacity;
    string newRepairStatus;

    cout << "请选择要修改的内容:" << endl;
    cout << "1. 修改房间号 " << endl;
    cout << "2. 修改房间容量 " << endl;
    cout << "3. 修改房间状态 " << endl;
    cout << "请输入选项 (1-3): ";
    int choice = getChoice();

    string sql = "UPDATE rooms SET ";

    // 根据用户选择修改相应的字段
    switch (choice)
    {
        case 1:
            cout << "请输入新的房间号: ";
            cin >> newRoomNumber;
            sql += "roomNumber = '" + newRoomNumber + "' ";
            cout << "修改房间号为 " << newRoomNumber << " 成功" << endl;
            break;
        case 2:
            while (newCapacity <= capacity)
            {
                cout << "请输入新的房间容量" << "(必须大于当前容量：" << capacity << "): ";
                cin >> newCapacity;
            } // 确保容量为正数
            sql += "capacity = " + to_string(newCapacity) + " ";
            cout << "修改房间容量为 " << newCapacity << " 成功" << endl;
            break;
        case 3:
            while (newRepairStatus != "正常" && newRepairStatus != "维修中")
            {
                cout << "请输入新的房间维修状态 (正常/维修中): ";
                cin >> newRepairStatus;
            }
            sql += "repair_status = '" + newRepairStatus + "' ";
            cout << "修改房间维修状态为 " << newRepairStatus << " 成功" << endl;
            break;
        default:
            cout << "无效的选项!" << endl;
            return;
    }

    // 附加 WHERE 子句，确保只更新指定的房间
    sql += "WHERE roomID = '" + selectedRoomID + "';";

    db.execute(sql);
}

// 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 // 管理用户 //
// 添加用户
void UserManager::addUser()
{
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
                if (studentExistsByID(userID))
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
            registerUser(userID, password, name, gender, contactInfo, false, false);
        }
    }
}

// 删除用户
void UserManager::deleteUser(const string &userID)
{
    bool flag = isStudentCheckedIn(userID);
    if (flag == true)
    {
        cout << "当前待删除用户已经入住，请先安排退宿\n";
        arrangeCheckOut(userID);
    }
    string confirmation;
    while (true)
    {
        cout << "请确认是否要删除以下用户？(yes or no)：\n";
        checkUserInfo(userID);
        getline(cin, confirmation);
        if (confirmation == "yes")
        {
            break;
        } else if (confirmation == "no")
        {
            cout << "删除操作已取消。\n";
            return;
        } else
        {
            cout << "无效输入，请输入 'yes' 或 'no'。\n";
        }
    }
    string sql = "DELETE FROM users WHERE userID = '" + userID + "';";
    execute(sql);
    cout << "用户删除成功\n";
}

// 通过ID查询用户信息
void UserManager::checkUserInfo(const string &userID)
{
    bool flag = isStudentCheckedIn(userID); //查询的同学是否已经入住
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
        query(sql);
        cout << "该学生暂未入住。\n";
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
        query(sql);
    }
}

// 通过姓名查询用户信息（支持模糊查询）
void UserManager::checkUserInfoByName(const string &userName)
{
    const string sql = "SELECT "
                       "    u.userID AS 学号,           -- 学生学号\n"
                       "    u.name AS 姓名,             -- 学生姓名\n"
                       "    u.gender AS 性别,           -- 学生性别\n"
                       "    COALESCE(u.password, 'NULL') AS 密码,         -- 学生密码，若为空则显示NULL\n"
                       "    COALESCE(u.contactInfo, 'NULL') AS 联系方式,  -- 学生联系方式，若为空则显示NULL\n"
                       "    COALESCE(d.name, 'NULL') AS 宿舍楼,           -- 宿舍楼名称，若为空则显示NULL\n"
                       "    COALESCE(r.roomNumber, 'NULL') AS 房间号      -- 房间号，若为空则显示NULL\n"
                       "FROM "
                       "    users u\n"
                       "LEFT JOIN "
                       "    student_rooms sr ON u.userID = sr.studentID  -- 连接学生表与学生房间关系表\n"
                       "LEFT JOIN "
                       "    rooms r ON sr.roomID = r.roomID  -- 连接房间表\n"
                       "LEFT JOIN "
                       "    dormitories d ON r.dormitoryID = d.dormitoryID  -- 连接宿舍楼表\n"
                       "WHERE "
                       "    u.name LIKE '%" + userName + "%';"; // 使用拼接的方式将userName插入查询条件

    // 调用Query方法，执行SQL查询
    if (queryExists(sql))
    {
        query(sql);
        return;
    }

    cout << "查询 ‘" << userName << "’ 无结果" << endl;
}

// 查询所有用户信息
void UserManager::checkUserInfoALL()
{
    string sql = "SELECT "
            "    u.userID AS 学号,           -- 学生学号\n"
            "    u.name AS 姓名,           -- 学生名称\n"
            "    u.gender AS 性别,           -- 学生性别\n"
            "    u.password AS 密码,           -- 学生密码\n"
            "    u.contactInfo AS 联系方式,           -- 学生联系方式\n"
            "    COALESCE(d.name, 'NULL') AS 宿舍楼,           -- 宿舍楼名称，如果没有宿舍返回NULL\n"
            "    COALESCE(r.roomNumber, 'NULL') AS 房间号        -- 房间号，如果没有房间返回NULL\n"
            "FROM "
            "    users u\n"
            "LEFT JOIN "
            "    student_rooms sr ON u.userID = sr.studentID   -- 左连接学生表与学生宿舍表\n"
            "LEFT JOIN "
            "    rooms r ON sr.roomID = r.roomID   -- 左连接房间表\n"
            "LEFT JOIN "
            "    dormitories d ON r.dormitoryID = d.dormitoryID -- 左连接宿舍楼表\n"
            ";";


    // 调用Query方法，执行SQL查询
    query(sql);
}

// 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 // 管理住宿 //
// 1. 安排住宿
void UserManager::arrangeAccommodation(const string &studentID)
{
    string dormitoryName, roomChoice;
    selectValidRoom(studentID, dormitoryName, roomChoice);
    string note;
    cout << "请输入入住备注（可选，按回车跳过）: ";
    getline(cin, note);
    quickArrangeAccommodation(studentID, dormitoryName, roomChoice, note);
}

// 一键入住
void UserManager::quickArrangeAccommodation(const string &studentID, const string &dormitoryName,
                                            const string &roomChoice, const string &note)
{
    string insert_room = "INSERT INTO student_rooms (studentID, roomID) "
                         "SELECT '" + studentID + "', r.roomID "
                         "FROM rooms r "
                         "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                         "WHERE d.name = '" + dormitoryName + "' "
                         "AND r.roomNumber = '" + roomChoice + "' "
                         "AND r.occupied < r.capacity;";
    execute(insert_room);

    string recordType = "入住"; // 固定为入住操作
    string eventTime = "CURRENT_TIMESTAMP"; // 默认使用当前时间

    // 插入入住记录
    // 获取备注信息


    string insert_check_in = "INSERT INTO check_in_out_records (studentID, roomID, eventTime, recordType, note) "
                             "VALUES ('" + studentID + "', (SELECT r.roomID FROM rooms r "
                             "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                             "WHERE d.name = '" + dormitoryName + "' "
                             "AND r.roomNumber = '" + roomChoice + "' "
                             "AND r.occupied < r.capacity LIMIT 1), " + eventTime + ", '" + recordType + "', '" + note +
                             "');";

    string updateCheckInStatus = "UPDATE users SET isCheckedIn = 1 WHERE userID = '" + studentID + "';";
    execute(updateCheckInStatus);
    // 执行插入操作
    execute(insert_check_in);

    cout << "住宿安排成功" << endl;
    db.updateRoomStatus();
}

// 2. 安排退宿
void UserManager::arrangeCheckOut(const string &studentID)
{
    string confirmation;
    while (true)
    {
        cout << "确认退宿操作？(yes/no)：";
        getline(cin, confirmation);
        if (confirmation == "yes")
        {
            break;
        } else if (confirmation == "no")
        {
            cout << "退宿操作已取消。\n";
            return;
        } else
        {
            cout << "无效输入，请输入 'yes' 或 'no'。\n";
        }
    }
    // 4. 获取退宿备注信息
    string note;
    cout << "请输入退宿备注（可选，按回车跳过）: ";
    getline(cin, note);
    quickArrangeCheckOut(studentID, note);
}

// 一键退宿
void UserManager::quickArrangeCheckOut(const string &studentID, const string &note)
{
    string studentName; // 获取学生名字
    string dormitoryName; // 获取宿舍楼名称
    string roomNumber; // 获取房间号
    //2. 获取学生的宿舍信息
    string getStudentRoomQuery = "SELECT u.name AS 姓名, d.name AS 宿舍楼, r.roomNumber AS 房间号 "
                                 "FROM users u "
                                 "JOIN student_rooms sr ON u.userID = sr.studentID "
                                 "JOIN rooms r ON sr.roomID = r.roomID "
                                 "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                                 "WHERE u.userID = '" + studentID + "';";


    // 执行查询
    db.query(getStudentRoomQuery);

    // 获取查询结果
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        studentName = db.getQueryResult(0); // 获取学生名字
        dormitoryName = db.getQueryResult(1); // 获取宿舍楼名称
        roomNumber = db.getQueryResult(2); // 获取房间号
        // 输出当前住宿信息
        // cout << "学生 " << studentName << " (" << studentID << ") 当前住宿在 "
        //         << dormitoryName << " 宿舍楼的 " << roomNumber << " 房间。\n";
    }

    // 4. 获取退宿备注信息

    // 获取当前时间作为退宿时间
    string eventTime = "CURRENT_TIMESTAMP"; // 使用数据库的时间

    // 5. 获取房间ID，确保返回有效值
    string getRoomIDQuery = "SELECT r.roomID FROM rooms r "
                            "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                            "WHERE d.name = '" + dormitoryName + "' AND r.roomNumber = '" + roomNumber +
                            "'  LIMIT 1;";

    db.queryExists(getRoomIDQuery);

    int roomID = 0;
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        roomID = sqlite3_column_int(db.stmt, 0); // 获取 roomID
    }

    if (roomID == 0)
    {
        cout << "无法找到对应的房间，可能是房间信息不匹配。\n";
        return;
    }

    // 6. 插入退宿记录到 check_in_out_records 表
    string insertCheckOutQuery = "INSERT INTO check_in_out_records (studentID, roomID, eventTime, recordType, note) "
                                 "VALUES ('" + studentID + "', " + to_string(roomID) + ", CURRENT_TIMESTAMP, '退宿', '" +
                                 note + "');";

    execute(insertCheckOutQuery);

    // 7. 更新学生的入住状态：将 isCheckedIn 设置为 0
    string updateCheckOutStatusQuery = "UPDATE users SET isCheckedIn = 0 WHERE userID = '" + studentID + "';";
    execute(updateCheckOutStatusQuery);


    // 9. 删除学生与房间的关系记录
    string deleteRoomAssignmentQuery = "DELETE FROM student_rooms WHERE studentID = '" + studentID + "';";
    execute(deleteRoomAssignmentQuery);

    // 10. 调用 db.updateRoomStatus 来更新房间的状态和占用人数
    db.updateRoomStatus();

    cout << "退宿操作成功，学生 " << studentName << " (学号：" << studentID << ")" << " 已从 " << dormitoryName << " 宿舍楼的 " <<
            roomNumber
            << " 房间退宿。\n";
}

// 3. 处理学生申请
void UserManager::dealAccommodationRequests()
{
    // 显示所有待审批的请求
    string studentID, dormitoryName, roomNumber, requestType;
    //string studentName, gender, requestTime, approveTime,status, note;
    // 使用 unordered_set 来存储请求ID，避免重复和加速查找
    unordered_set<string> requestIDs;
    const string sql = R"(
SELECT ar.requestID
FROM accommodation_requests ar
WHERE ar.status = '待审批'
ORDER BY ar.requestTime DESC;
    )";

    db.queryExists(sql);

    // 遍历查询结果并显示每个申请的信息
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        // 获取查询结果中的每一列数据
        string requestID = db.getQueryResult(0); // 申请ID
        // 将请求ID存入 unordered_set
        requestIDs.insert(requestID);
    }

    // 如果没有待审批的请求
    if (requestIDs.empty())
    {
        cout << "没有待审批的申请。\n";
        return;
    }
    viewAccommodationRequests();

    string selectedRequestID;
    // 提示管理员选择处理的请求ID
    while (true)
    {
        cout << "请输入要处理的请求ID（输入 'exit' 退出）：";
        cin >> selectedRequestID;

        // 如果输入 'exit'，退出
        if (selectedRequestID == "exit")
        {
            cout << "退出成功。\n";
            return;
        }

        // 验证请求ID是否有效
        if (requestIDs.find(selectedRequestID) != requestIDs.end())
        {
            viewAccommodationRequests(selectedRequestID);
            while (sqlite3_step(db.stmt) == SQLITE_ROW)
            {
                // 获取查询结果中的每一列数据
                // requestID = db.getQueryResult(0); // 申请ID
                studentID = db.getQueryResult(1); // 学生学号
                // studentName = db.getQueryResult(2); // 学生姓名
                // gender = db.getQueryResult(3); // 学生性别
                dormitoryName = db.getQueryResult(4); // 申请宿舍楼名称
                roomNumber = db.getQueryResult(5); // 申请房间号
                requestType = db.getQueryResult(6); // 申请类型
                // requestTime = db.getQueryResult(7); // 申请时间
                // approveTime = db.getQueryResult(8); // 审批时间
                // status = db.getQueryResult(9); // 申请状态
                // note = db.getQueryResult(10); // 备注
            }
            //cout << studentName << " " << studentID << " " << dormitoryName << " " << roomNumber << " " << endl;
            // 请求ID有效，提示管理员选择审批操作
            SlowPrint("●选择审批操作●", 30, 0);
            MenuPrint("UP", 30);
            MenuPrint("1、通过", 30);
            MenuPrint("2、不通过", 30);
            MenuPrint("3、返回", 30);
            MenuPrint("DOWN", 30);
            SlowPrint("请输入您的选择：", 30, -1);
            // cout << "\n选择审批操作：\n";
            // cout << "1. 通过\n";
            // cout << "2. 不通过\n";
            // cout << "3. 返回\n";
            //
            //
            // cout << "请输入选择：";
            int choice = getChoice();
            cin.ignore();
            // 处理选择
            switch (choice)
            {
                case 1: // 通过
                    cout << "你选择了通过请求ID: " << selectedRequestID << endl;

                    if (requestType == "入住")
                    {
                        // 处理入住申请
                        arrangeAccommodation(studentID);
                    } else if (requestType == "换宿")
                    {
                        quickArrangeCheckOut(studentID, "申请的换宿");
                        quickArrangeAccommodation(studentID, dormitoryName, roomNumber, "申请的换宿");
                        // 处理换宿申请
                    } else if (requestType == "退宿")
                    {
                        // 处理退宿申请
                        quickArrangeCheckOut(studentID, "申请的退宿");
                    }
                    updateApprovalStatus(selectedRequestID, "已审批");
                    requestIDs.erase(selectedRequestID);
                    break;

                case 2: // 不通过
                    cout << "你选择了不通过请求ID: " << selectedRequestID << endl;
                    updateApprovalStatus(selectedRequestID, "已拒绝");
                    requestIDs.erase(selectedRequestID);
                    return;

                case 3: // 返回
                    cout << "返回成功，\n";
                    break; // 返回上层菜单

                default:
                    cout << "无效选择，请重新选择。\n";
                    break;
            }
        } else
        {
            cout << "无效的请求ID，请重新选择。\n";
        }

        // 检查是否所有请求都已处理完毕
        if (requestIDs.empty())
        {
            cout << "所有申请已经处理完毕。\n";
            return;
        }
    }
}

// 更新审批状态
void UserManager::updateApprovalStatus(const string &requestID, const string &status)
{
    // 更新审批状态的函数，修改申请记录的状态
    string updateQuery =
            "UPDATE accommodation_requests SET status = ?, approveTime = CURRENT_TIMESTAMP WHERE requestID = ?";
    db.executeWithParams(updateQuery, {status, requestID});
}

// 查看申请（输入为空则查询所有，输入为指定则查询指定）
void UserManager::viewAccommodationRequests(const string &requestID)
{
    string sql;

    // 如果传入了请求ID，则查询指定请求
    if (!requestID.empty())
    {
        // 拼接 SQL 查询字符串
        sql = "SELECT "
              "ar.requestID AS 申请ID, "
              "u.userID AS 学生学号, "
              "u.name AS 姓名, "
              "u.gender AS 性别, "
              "ar.dormitoryName AS 申请宿舍楼, "
              "ar.roomNumber AS 申请房间号, "
              "ar.requestType AS 申请类型, "
              "ar.requestTime AS 申请时间, "
              "ar.approveTime AS 审批时间, "
              "ar.status AS 申请状态, "
              "ar.note AS 备注 "
              "FROM "
              "accommodation_requests ar "
              "JOIN "
              "users u ON ar.studentID = u.userID "
              "WHERE "
              "ar.requestID = '" + requestID + "' "
              "ORDER BY "
              "ar.requestTime DESC;";
        db.queryExists(sql);
    } else
    {
        // 如果没有传入请求ID，则查询所有待审批的申请
        sql = "SELECT "
                "ar.requestID AS 申请ID, "
                "u.userID AS 学生学号, "
                "u.name AS 姓名, "
                "u.gender AS 性别, "
                "ar.dormitoryName AS 申请宿舍楼, "
                "ar.roomNumber AS 申请房间号, "
                "ar.requestType AS 申请类型, "
                "ar.requestTime AS 申请时间, "
                "ar.approveTime AS 审批时间, "
                "ar.status AS 申请状态, "
                "ar.note AS 备注 "
                "FROM "
                "accommodation_requests ar "
                "JOIN "
                "users u ON ar.studentID = u.userID "
                "WHERE "
                "ar.status = '待审批' "
                "ORDER BY "
                "ar.requestTime DESC;";
        db.query(sql);
    }

    // 直接调用 db.Query() 执行拼接后的查询
}

// 4. 查看入住退宿记录
void UserManager::viewCheckInOutRecords(const string &studentID)
{
    string sql;

    if (studentID.empty())
    {
        // 如果没有提供学生ID，查询所有记录
        sql = "SELECT recordID AS 记录ID, "
                "studentID AS 学生ID, "
                "roomID AS 房间ID, "
                "eventTime AS 事件时间, "
                "recordType AS 记录类型, "
                "note AS 备注 "
                "FROM check_in_out_records;";
    } else
    {
        // 如果提供了学生ID，查询该学生的所有记录
        sql = "SELECT recordID AS 记录ID, "
              "studentID AS 学生ID, "
              "roomID AS 房间ID, "
              "eventTime AS 事件时间, "
              "recordType AS 记录类型, "
              "note AS 备注 "
              "FROM check_in_out_records "
              "WHERE studentID = '" + studentID + "';";
    }

    // 执行查询
    if (!db.query(sql))
    {
        cout << "您查询的 '" << studentID << "' 无记录。" << endl;
    }
}

// 5. 查看没有入住的学生
void UserManager::checkUserNotCheckedIn()
{
    string sql = "SELECT "
            "    u.userID AS 学号,           -- 学生学号\n"
            "    u.name AS 姓名,           -- 学生名称\n"
            "    u.gender AS 性别,           -- 学生性别\n"
            "    u.password AS 密码,           -- 学生密码\n"
            "    u.contactInfo AS 联系方式,           -- 学生联系方式\n"
            "    COALESCE(d.name, 'NULL') AS 宿舍楼,           -- 宿舍楼名称，如果没有宿舍返回NULL\n"
            "    COALESCE(r.roomNumber, 'NULL') AS 房间号        -- 房间号，如果没有房间返回NULL\n"
            "FROM "
            "    users u\n"
            "LEFT JOIN "
            "    student_rooms sr ON u.userID = sr.studentID   -- 左连接学生表与学生宿舍表\n"
            "LEFT JOIN "
            "    rooms r ON sr.roomID = r.roomID   -- 左连接房间表\n"
            "LEFT JOIN "
            "    dormitories d ON r.dormitoryID = d.dormitoryID -- 左连接宿舍楼表\n"
            "WHERE "
            "    sr.studentID IS NULL  -- 筛选没有入住的学生\n"
            "    AND u.isAdmin = 0;    -- 筛选出不是管理员的学生\n";


    // 调用Query方法，执行SQL查询
    query(sql);
}

// 处理维修请求 // 处理维修请求 // 处理维修请求 // 处理维修请求 // 处理维修请求 // 处理维修请求 // 处理维修请求 // 处理维修请求 //
void UserManager::handleRepairRequests()
{
    // 1. 查询所有未处理的维修请求
    string sql = "SELECT repairID AS '报修ID', studentID AS '学生ID', roomID AS '房间ID', "
            "repairType AS '种类', description AS '描述', repairTime AS '报修时间' "
            "FROM repair_requests "
            "WHERE status = '未处理';";

    // 执行查询
    db.query(sql);

    // 2. 如果没有未处理的报修请求
    if (sqlite3_step(db.stmt) != SQLITE_ROW)
    {
        cout << "没有待处理的报修请求。\n";
        return; // 没有待处理的报修请求，直接退出
    }

    // 4. 获取管理员输入的 repairID
    string selectedRepairID;
    cout << "\n请输入要处理的报修ID（输入'exit'退出）：";
    cin >> selectedRepairID;

    // 输入'退出'，结束函数
    if (selectedRepairID == "exit")
    {
        cout << "已退出处理报修请求。\n";
        return;
    }

    // 5. 验证输入的 repairID 是否有效
    string queryExists = "SELECT 1 FROM repair_requests WHERE repairID = '" + selectedRepairID + "' AND status = '未处理'";
    if (!db.queryExists(queryExists))
    {
        cout << "无效的报修ID，未找到待处理的报修请求。\n";
        return;
    }

    // 6. 确认处理报修请求
    cout << "确认处理报修请求ID: " << selectedRepairID << " 吗？(yes/no): ";
    string confirm;
    cin >> confirm;

    if (confirm == "yes")
    {
        // 7. 更新报修请求的状态为 '已处理'，并记录处理时间
        string updateRepairRequestSQL = "UPDATE repair_requests "
                                        "SET status = '已处理', handleTime = CURRENT_TIMESTAMP "
                                        "WHERE repairID = '" + selectedRepairID + "';";
        db.execute(updateRepairRequestSQL);

        // 8. 获取房间ID，更新房间状态
        string queryRoomID = "SELECT roomID FROM repair_requests WHERE repairID = '" + selectedRepairID + "';";
        db.queryExists(queryRoomID);

        string roomID;
        if (sqlite3_step(db.stmt) == SQLITE_ROW)
        {
            roomID = db.getQueryResult(0); // 获取房间ID
        }

        string checkPendingRepairsSQL = "SELECT 1 FROM repair_requests "
                                        "WHERE roomID = '" + roomID + "' AND status = '未处理' LIMIT 1;";
        if (db.queryExists(checkPendingRepairsSQL))
        {
            // 如果该房间还有未处理的报修请求，不能将房间状态更新为 '正常'
            cout << "房间仍有待处理的报修请求，房间状态保持为 '维修中'。\n";
        } else
        {
            // 否则，更新房间状态为 '正常'
            string updateRoomSQL = "UPDATE rooms "
                                   "SET repair_status = '正常' "
                                   "WHERE roomID = '" + roomID + "';";
            db.execute(updateRoomSQL);
            cout << "该房间所有报修请求已处理，状态已更新为 '正常'。\n";
        }
    } else
    {
        cout << "取消处理该报修请求。\n";
    }
}

// 入住报表
void UserManager::generateAccommodationRateReport()
{
    int timeChoice;

    cout << "\n请选择生成报表的时间范围：\n";
    cout << "1. 当前月\n";
    cout << "2. 当前年\n";
    cout << "请输入选择：";

    while (true)
    {
        cin >> timeChoice;
        if (timeChoice < 1 || timeChoice > 2)
        {
            cout << "无效选择，请重新输入：";
            continue;
        }
        if (cin.fail()) // 清除输入缓冲区
        {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
            cout << "输入无效，请输入有效数字：";
            continue;
        }
        break;
    }


    string sql;
    if (timeChoice == 1)
    {
        // 获取当前月的住宿率报表 SQL 查询
        sql = R"(
        SELECT d.name   AS 宿舍楼名称,
       -- 统计当前月已入住的学生人数，确保每个学生只计算一次
       COUNT(DISTINCT CASE
                          WHEN strftime('%Y-%m', co.eventTime) = strftime('%Y-%m', 'now')
                              AND co.recordType = '入住'
                              THEN co.studentID
           END) AS 当前月已入住人数,
       -- 通过子查询单独计算宿舍楼的总房间容量，避免因JOIN导致的重复计算
       rc.总房间容量,
       -- 计算入住率：已入住人数 / 总房间容量，并保留两位小数
       ROUND(
               COUNT(DISTINCT CASE
                                  WHEN strftime('%Y-%m', co.eventTime) = strftime('%Y-%m', 'now')
                                      AND co.recordType = '入住'
                                      THEN co.studentID
                   END) * 1.0 / rc.总房间容量,
               2
       )        AS 入住率
FROM dormitories d
         -- 子查询：计算每个宿舍楼的总房间容量
         LEFT JOIN (SELECT dormitoryID,
                           SUM(capacity) AS 总房间容量
                    FROM rooms
                    GROUP BY dormitoryID) rc ON d.dormitoryID = rc.dormitoryID
    -- 连接 rooms 和 check_in_out_records 表，用于统计入住人数
         LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
         LEFT JOIN check_in_out_records co ON r.roomID = co.roomID
GROUP BY d.dormitoryID; -- 按宿舍楼分组，确保宿舍楼数据汇总
    )";
    } else if (timeChoice == 2)
    {
        // 获取当前年入住率报表 SQL 查询
        sql = R"(
        SELECT
            d.name AS 宿舍楼名称,
            -- 统计当前年度已入住的学生人数，确保每个学生只计算一次
            COUNT(DISTINCT CASE
                WHEN strftime('%Y', co.eventTime) = strftime('%Y', 'now')
                     AND co.recordType = '入住'
                THEN co.studentID
            END) AS 当前年度已入住人数,
            -- 通过子查询单独计算宿舍楼的总房间容量，避免因JOIN导致的重复计算
            rc.总房间容量,
            -- 计算入住率：已入住人数 / 总房间容量，并保留两位小数
            ROUND(
                COUNT(DISTINCT CASE
                    WHEN strftime('%Y', co.eventTime) = strftime('%Y', 'now')
                         AND co.recordType = '入住'
                    THEN co.studentID
                END) * 1.0 / rc.总房间容量,
                2
            ) AS 入住率
        FROM dormitories d
        -- 子查询：计算每个宿舍楼的总房间容量
        LEFT JOIN (
            SELECT
                dormitoryID,
                SUM(capacity) AS 总房间容量
            FROM rooms
            GROUP BY dormitoryID
        ) rc ON d.dormitoryID = rc.dormitoryID
        -- 连接 rooms 和 check_in_out_records 表，用于统计入住记录
        LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
        LEFT JOIN check_in_out_records co ON r.roomID = co.roomID
        GROUP BY d.dormitoryID;  -- 按宿舍楼分组，确保宿舍楼数据汇总
    )";
    }
    system("cls");
    loading("正在查询中", 50, 10);
    SlowPrint("查询完成", 50, 0);
    Sleep(100);
    cout << "\n---- 入住率报表 ----\n";
    query(sql);
    SlowPrint("请按任意键继续", 30, -1);
    getch();
    system("cls");
    // 模拟查询并打印结果
}


// 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 // 学生菜单 //

// 学生注册


void UserManager::studentRegister()
{
    string studentID, password, name, gender, contactInfo;
    SlowPrint("●学生注册●", 30, 0);
    //cout << "\n---- 学生注册 ----\n";
    //cout << "请输入学号: ";
    SlowPrint("请输入学号: ", 30, -1);
    cin >> studentID;
    SlowPrint("请输入密码: ", 30, -1);
    //cout << "请输入密码: ";
    cin >> password;
    SlowPrint("请输入姓名: ", 30, -1);
    //cout << "请输入姓名: ";
    cin >> name;
    SlowPrint("请输入性别: ", 30, -1);
    //cout << "请输入性别: ";
    while (gender != "男" && gender != "女")
    {
        cout << "请输入性别(男/女): ";
        cin >> gender;
    }
    SlowPrint("请输入联系方式: ", 30, -1);
    //cout << "请输入联系方式: ";
    cin >> contactInfo;
    registerUser(studentID, password, name, gender, contactInfo, false, false);
    system("cls");
    loading("正在注册中", 50, 100);
    SlowPrint("注册成功！", 50, 0);
    Sleep(3000);
    system("cls");
}

// 1. 查看宿舍楼和房间信息
void UserManager::viewDormitoryInfo(const string &stuID)
{
    if (isStudentCheckedIn(stuID))
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

        db.query(sql);
        db.query(sql2);
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

// 检查是否有待审批的申请
bool UserManager::hasPendingApplication(const string &studentID)
{
    // 构造SQL查询语句，拼接学生ID来查询该学生是否有待审批的申请
    string query = "SELECT COUNT(*) FROM accommodation_requests "
                   "WHERE studentID = '" + studentID + "' "
                   "AND status = '待审批';";

    // 执行查询
    db.queryExists(query);

    // 如果查询结果返回的是一行数据
    if (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        int pendingApplications = stoi(db.getQueryResult(0)); // 获取待审批的申请数量

        // 如果待审批的申请数量大于0，表示该学生有待审批的申请
        if (pendingApplications > 0)
        {
            //cout << "学生 " << studentID << " 有待审批的申请。\n";
            return true;
        } else
        {
            //cout << "学生 " << studentID << " 没有待审批的申请。\n";
            return false;
        }
    }

    // 如果查询失败
    cout << "查询失败，无法获取数据。\n";
    return false;
}

// 2. 申请入住
void UserManager::applyMoveIn(const string &stuID)
{
    if (isStudentCheckedIn(stuID))
    {
        cout << "您已经入住！" << endl;
        return;
    }
    // 构建 SQL 查询语句，仅插入学生 ID 和申请类型
    string sql = "INSERT INTO accommodation_requests (studentID, requestType) "
                 "VALUES ('" + stuID + "', '入住');";

    // 执行 SQL 语句
    db.execute(sql);
    cout << "申请入住成功" << endl;
}

// 3. 申请退宿
void UserManager::applyMoveOut(const string &stuID)
{
    if (!isStudentCheckedIn(stuID))
    {
        cout << "您尚未入住！" << endl;
        return;
    }
    // 构建 SQL 查询语句，仅插入学生 ID 和申请类型
    string sql = "INSERT INTO accommodation_requests (studentID, requestType) "
                 "VALUES ('" + stuID + "', '退宿');";

    // 执行 SQL 语句
    execute(sql);
    cout << "申请退宿成功" << endl;
}

// 4. 请求换宿
void UserManager::requestRoomChange(const string &studentID)
{
    string dormitoryName, roomChoice, currentRoom, note;
    cin.ignore();
    selectValidRoom(studentID, dormitoryName, roomChoice);
    cout << "请输入换宿备注（可选，按回车跳过）: ";
    getline(cin, note);
    string sql = "INSERT INTO accommodation_requests (studentID, dormitoryName, roomNumber, requestType, note) "
                 "SELECT '" + studentID + "', '" + dormitoryName + "', r2.roomNumber, '换宿', '' "
                 "FROM rooms r2 "
                 "WHERE r2.roomNumber = '" + roomChoice + "' " // 目标房间号
                 "AND r2.dormitoryID = (SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "');";
    // 执行 SQL 语句
    db.execute(sql);
    cout << "换宿申请已提交，等待宿管处理。\n";
}

// 5. 提交维修请求
void UserManager::createRepairRequest(const string &studentID)
{
    // 查询该学生所在的房间号
    cin.ignore(); // 清除输入缓存
    string queryRoom = "SELECT r.roomNumber "
                       "FROM rooms r "
                       "JOIN student_rooms sr ON r.roomID = sr.roomID "
                       "WHERE sr.studentID = '" + studentID + "';";

    db.queryExists(queryRoom);

    // 获取房间号
    string roomNumber;
    if (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        roomNumber = db.getQueryResult(0); // 获取房间号
    } else
    {
        cout << "未找到该学生的房间号。\n";
        return;
    }

    // 获取报修描述和类型
    string description, repairType;

    // 获取报修类型
    cout << "请选择报修类型（泥、木、水、电、设备、其它）: ";
    cin >> repairType;

    // 检查报修类型是否合法
    if (repairType != "泥" && repairType != "木" && repairType != "水" && repairType != "电" && repairType != "设备" &&
        repairType != "其它")
    {
        cout << "无效的报修类型。请重新输入有效的类型。\n";
        return;
    }
    // 获取报修描述
    cout << "请输入报修描述: ";
    cin.ignore();
    getline(cin, description);
    // 构建SQL插入语句
    string sql = "INSERT INTO repair_requests (studentID, roomID, description, repairType) "
                 "VALUES ('" + studentID + "', "
                 "(SELECT roomID FROM rooms WHERE roomNumber = '" + roomNumber + "' LIMIT 1), "
                 "'" + description + "', '" + repairType + "');";

    // 执行SQL语句
    db.execute(sql);
    // 更新房间的维修状态为“维修中”
    string updateRepairStatus = "UPDATE rooms SET repair_status = '维修中' "
                                "WHERE roomNumber = '" + roomNumber + "';";

    // 执行更新房间状态的SQL语句
    db.execute(updateRepairStatus);
    cout << "报修记录已成功提交。\n";
}

// 6. 查看通知
void UserManager::viewNotifications(const string &stuID)
{
    string a = stuID;
}

// 7. 查看自己所有请求
void UserManager::viewRequests(const string &stuID)
{
    string sql =
            "SELECT requestID AS \"申请ID\", requestType AS \"申请类型\", status AS \"申请状态\",dormitoryName AS \"宿舍楼名称\", "
            "roomNumber AS \"房间号\",  requestTime AS \"申请时间\", "
            "approveTime AS \"审批时间\", note AS \"备注\" "
            "FROM accommodation_requests "
            "WHERE studentID = '" + stuID + "' "
            "ORDER BY requestTime DESC;";
    db.query(sql);
}

// 学生查看未审批的请求
void UserManager::viewApprovingRequests(const string &stuID)
{
    // 构造SQL查询语句，查询待审批的申请
    string sql =
            "SELECT requestID AS \"申请ID\", "
            "       requestType AS \"申请类型\", "
            "       status AS \"申请状态\", "
            "       dormitoryName AS \"宿舍楼名称\", "
            "       roomNumber AS \"房间号\", "
            "       requestTime AS \"申请时间\", "
            "       approveTime AS \"审批时间\", "
            "       note AS \"备注\" "
            "FROM accommodation_requests "
            "WHERE studentID = '" + stuID + "' "
            "AND status = '待审批' " // 仅查询待审批的申请
            "ORDER BY requestTime DESC;"; // 按申请时间降序排列

    // 执行查询
    db.query(sql);
}
