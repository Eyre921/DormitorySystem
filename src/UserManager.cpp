#include "UserManager.h"
#include <iostream>

using namespace std;

// 构造函数，自动连接数据库
UserManager::UserManager() : db("../data/dormitory.db")
{
    db.updateRoomStatus();
    // 直接在这里指定数据库路径
    // 在这里，可以进行数据库的初始化（例如创建表等操作）
    // if (!db.execute(
    //     "CREATE TABLE IF NOT EXISTS users (userID TEXT PRIMARY KEY, name TEXT, gender TEXT, password TEXT, contactInfo TEXT, isCheckedIn INTEGER DEFAULT 0, isAdmin INTEGER DEFAULT 0);"))
    // {
    //     cout << "数据库创建失败！\n";
    //     exit(1); // 如果数据库创建失败，退出程序
    // }
}

// 用户登录
bool UserManager::loginUser(const string &userID, const string &password, const string &isAdmin)
{
    string sql = "SELECT * FROM users WHERE userID = '" + userID + "' AND password = '" + password + "' AND isAdmin = '"
                 + isAdmin + "';";

    if (db.QueryExists(sql))
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

// 获取所有用户
void UserManager::getAllUsers()
{
    db.Query("SELECT * FROM users;");
}

void UserManager::Query(const string &SQL)
{
    db.Query(SQL);
}

void UserManager::execute(const string &SQL)
{
    db.execute(SQL);
}

bool UserManager::queryExists(const string &SQL)
{
    return db.QueryExists(SQL);
}

bool UserManager::dormitoryExistsByName(const string &dormitoryName)
{
    // 模拟查询语句
    string sql = "SELECT * FROM dormitories WHERE name = '" + dormitoryName + "';";

    // 调用查询函数来检查数据库中是否已有该宿舍楼名称
    if (db.QueryExists(sql))
    {
        return true; // 如果返回 true，表示该宿舍楼名称已存在
    } else
    {
        return false; // 如果没有找到，表示该宿舍楼名称不存在
    }
}

bool UserManager::studentExistsByID(const string &ID)
{
    // 模拟查询语句
    string sql = "SELECT * FROM users WHERE userID = '" + ID + "';";
    return db.QueryExists(sql);
}

int UserManager::getDormitoryIDByName(const string &dormitoryName)
{
    return db.getDormitoryIDByName(dormitoryName);
}

bool UserManager::hasStudentsInDormitoryRooms(const string &checkRoomsSql)
{
    return db.hasStudentsInDormitoryRooms(checkRoomsSql);
}

bool UserManager::UserPasswordChange(const string &userID)
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

void UserManager::arrangeAccommodation()
{
    string studentID = Get_ID();
    if ("exit" == studentID) return;
    while (true)
    {
        // 检查是否已经入住
        if (IsStudentCheckedIn(studentID))
        {
            // 学生已经入住
            cout << "该学生已经入住，请重新选择其他学生。\n";
            studentID = Get_ID();
            continue;
        }
        break; // 如果学号存在且未入住，则退出循环，继续后续操作
    }
    string free_dorm =
            "SELECT d.name AS dormitoryName, d.sex, d.position, r.roomID, r.roomNumber, r.capacity, r.occupied "
            "FROM dormitories d "
            "JOIN rooms r ON d.dormitoryID = r.dormitoryID "
            "JOIN users u ON u.gender = d.sex " // 确保宿舍楼性别与用户性别匹配
            "WHERE r.occupied < r.capacity "
            "AND r.repair_status = '正常' "
            "AND u.userID = '" + studentID + "' " // 使用当前学生的 studentID
            "ORDER BY d.name, r.roomNumber;";

    Query(free_dorm);
    string dormitoryName;
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

        // 使用 queryExists 来检查宿舍楼是否存在并且有空房间
        if (!queryExists(queryAvailableRooms))
        {
            cout << "宿舍楼名称不正确或没有空房间，请重新输入。\n";
            continue;
        }
        break;
    }

    // 查询宿舍楼下所有空房间号（已入住为0）

    string query = "SELECT r.roomNumber, r.capacity, r.occupied "
                   "FROM rooms r "
                   "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                   "WHERE d.name = '" + dormitoryName + "' "
                   "AND r.occupied < r.capacity;";
    // 使用 Query 查询空闲房间
    Query(query);

    string roomChoice;
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

        // 使用 queryExists 来检查房间号是否存在并且可用
        if (!queryExists(queryRoomExists))
        {
            cout << "房间号不正确或已满，请重新输入。\n";
            continue;; // 如果房间无效，返回并重新开始
        }
        break;
    }

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
    string note;
    cout << "请输入入住备注（可选，按回车跳过）: ";
    getline(cin, note);

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

void UserManager::arrangeCheckOut(const string &studentID)
{
    string studentName; // 获取学生名字
    string dormitoryName; // 获取宿舍楼名称
    string roomNumber; // 获取房间号

    // 2. 获取学生的宿舍信息
    string getStudentRoomQuery = "SELECT u.name AS studentName, d.name AS dormitoryName, r.roomNumber "
                                 "FROM users u "
                                 "JOIN student_rooms sr ON u.userID = sr.studentID "
                                 "JOIN rooms r ON sr.roomID = r.roomID "
                                 "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                                 "WHERE u.userID = '" + studentID + "';";

    // 执行查询
    db.Query(getStudentRoomQuery);

    // 获取查询结果并输出
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        studentName = db.getQueryResult(0); // 获取学生名字
        dormitoryName = db.getQueryResult(1); // 获取宿舍楼名称
        roomNumber = db.getQueryResult(2); // 获取房间号

        // 输出当前住宿信息
        cout << "学生 " << studentName << " (" << studentID << ") 当前住宿在 "
                << dormitoryName << " 宿舍楼的 " << roomNumber << " 房间。\n";
    }

    // 3. 询问用户是否确认退宿
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

    // 获取当前时间作为退宿时间
    string eventTime = "CURRENT_TIMESTAMP"; // 使用数据库的时间

    // 5. 获取房间ID，确保返回有效值
    string getRoomIDQuery = "SELECT r.roomID FROM rooms r "
                            "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                            "WHERE d.name = '" + dormitoryName + "' AND r.roomNumber = '" + roomNumber +
                            "'  LIMIT 1;";

    db.Query(getRoomIDQuery);

    int roomID = 0;
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        roomID = sqlite3_column_int(db.stmt, 0); // 获取 roomID
    }

    if (roomID == 0)
    {
        cout << "无法找到对应的房间，可能是房间已满或房间信息不匹配。\n";
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

    cout << "退宿操作成功，学生 " << studentName << " (" << studentID << ")" << " 已从 " << dormitoryName << " 宿舍楼的 " << roomNumber
            << " 房间退宿。\n";
}

bool UserManager::IsStudentCheckedIn(const string &studentID)
{
    string checkCheckedInQuery = "SELECT isCheckedIn FROM users WHERE userID = '" + studentID +
                                 "' AND isCheckedIn = 1;";

    return queryExists(checkCheckedInQuery);
}

bool UserManager::IDExists(const string &studentID)
{
    string checkStudentQuery = "SELECT 1 FROM users WHERE userID = '" + studentID +
                               "' AND isAdmin = 0;";
    return queryExists(checkStudentQuery);
}

string UserManager::Get_ID()
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

void UserManager::checkUserInfo(const string &userID)
{
    bool flag = IsStudentCheckedIn(userID); //查询的同学是否已经入住
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
        Query(sql);
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
        Query(sql);
    }
}
