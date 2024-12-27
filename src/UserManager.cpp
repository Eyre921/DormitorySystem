#include "UserManager.h"
#include <iostream>
#include <unordered_set>

using namespace std;

// 构造函数，自动连接数据库
UserManager::UserManager() : db("../data/dormitory.db")
{
    db.updateRoomStatus();
    // cout << "数据库链接成功" << endl;
    // cout << "数据库状态更新成功" << endl;
    // 数据库链接成功
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

void UserManager::arrangeAccommodation(const string &studentID)
{
    string dormitoryName, roomChoice;
    SelectValidRoom(studentID, dormitoryName, roomChoice);
    string note;
    cout << "请输入入住备注（可选，按回车跳过）: ";
    getline(cin, note);
    QuickArrangeAccommodation(studentID, dormitoryName, roomChoice, note);
}

void UserManager::QuickArrangeAccommodation(const string &studentID, const string &dormitoryName,
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
} //一键入住
void UserManager::SelectValidRoom(const string &studentID, string &dormitoryName, string &roomChoice)
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


    Query(free_dorm);

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

    string query = "SELECT r.roomNumber AS 房间号, r.capacity AS 房间容量, r.occupied AS 已入住人数 "
                   "FROM rooms r "
                   "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                   "WHERE d.name = '" + dormitoryName + "' "
                   "AND r.occupied < r.capacity;";

    // 使用 Query 查询空闲房间
    Query(query);


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
}

void UserManager::requestRoomChange(const string &studentID)
{
    string dormitoryName, roomChoice, currentRoom, note;
    cin.ignore();
    SelectValidRoom(studentID, dormitoryName, roomChoice);
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
    QuickArrangeCheckOut(studentID, note);
}

void UserManager::QuickArrangeCheckOut(const string &studentID, const string &note)
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
    db.Query(getStudentRoomQuery);

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

    db.QueryExists(getRoomIDQuery);

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
} //一键退宿

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
        Query(sql);
    }
}

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
                       "    u.name = '" + userName + "';"; // 使用拼接的方式将userName插入查询条件

    // 调用Query方法，执行SQL查询
    if (queryExists(sql))
    {
        Query(sql);
        return;
    }

    cout << "查询 ‘" << userName << "’ 无结果" << endl;
}

void UserManager::checkUserInfoALL()
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
            ";";
    // 调用Query方法，执行SQL查询
    Query(sql);
}

void UserManager::deleteUser(const string &userID)
{
    bool flag = IsStudentCheckedIn(userID);
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

void UserManager::DealAccommodationRequests()
{
    // 显示所有待审批的请求
    string requestID, studentID, studentName, gender, dormitoryName, roomNumber, requestType, requestTime, approveTime,
            status, note;
    // 使用 unordered_set 来存储请求ID，避免重复和加速查找
    unordered_set<string> requestIDs;
    const string sql = R"(
SELECT ar.requestID
FROM accommodation_requests ar
WHERE ar.status = '待审批'
ORDER BY ar.requestTime DESC;
    )";

    db.QueryExists(sql);

    // 遍历查询结果并显示每个申请的信息
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        // 获取查询结果中的每一列数据
        requestID = db.getQueryResult(0); // 申请ID
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
                requestID = db.getQueryResult(0); // 申请ID
                studentID = db.getQueryResult(1); // 学生学号
                studentName = db.getQueryResult(2); // 学生姓名
                gender = db.getQueryResult(3); // 学生性别
                dormitoryName = db.getQueryResult(4); // 申请宿舍楼名称
                roomNumber = db.getQueryResult(5); // 申请房间号
                requestType = db.getQueryResult(6); // 申请类型
                requestTime = db.getQueryResult(7); // 申请时间
                approveTime = db.getQueryResult(8); // 审批时间
                status = db.getQueryResult(9); // 申请状态
                note = db.getQueryResult(10); // 备注
            }
            cout << studentName << " " << studentID << " " << dormitoryName << " " << roomNumber << " " << endl;
            // 请求ID有效，提示管理员选择审批操作
            cout << "\n选择审批操作：\n";
            cout << "1. 通过\n";
            cout << "2. 不通过\n";
            cout << "3. 返回\n";

            int choice;
            cout << "请输入选择（1/2/3）：";
            cin >> choice;
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
                        QuickArrangeCheckOut(studentID, "申请的换宿");
                        QuickArrangeAccommodation(studentID, dormitoryName, roomNumber, "申请的换宿");
                        // 处理换宿申请
                    } else if (requestType == "退宿")
                    {
                        // 处理退宿申请
                        QuickArrangeCheckOut(studentID, "申请的退宿");
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


void UserManager::updateApprovalStatus(const string &requestID, const string &status)
{
    // 更新审批状态的函数，修改申请记录的状态
    string updateQuery =
            "UPDATE accommodation_requests SET status = ?, approveTime = CURRENT_TIMESTAMP WHERE requestID = ?";
    db.executeWithParams(updateQuery, {status, requestID});
}


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
        db.QueryExists(sql);
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
        db.Query(sql);
    }

    // 直接调用 db.Query() 执行拼接后的查询
}


void UserManager::checkRoomOccupancy(int dormitoryID, const string &roomNumber)
{
    // 查询指定楼栋和房间的居住情况
    string queryRoom = R"(
        SELECT r.roomID, r.roomNumber, r.capacity, r.occupied
        FROM rooms r
        WHERE r.dormitoryID = ? AND r.roomNumber = ?
    )";

    vector<string> params = {to_string(dormitoryID), roomNumber};
    db.QueryWithParams(queryRoom, params);

    if (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        int roomID = stoi(db.getQueryResult(0));
        string roomNumber = db.getQueryResult(1);
        int capacity = stoi(db.getQueryResult(2));
        int occupied = stoi(db.getQueryResult(3));

        // 打印房间的居住情况
        cout << "房间号: " << roomNumber << ", 容量: " << capacity << ", 已入住: " << occupied << endl;

        // 如果房间有人入住，查询该房间的住户
        if (occupied > 0)
        {
            string queryStudents = "SELECT sr.studentID FROM student_rooms sr WHERE sr.roomID = ?";
            vector<string> studentParams = {to_string(roomID)};
            db.QueryWithParams(queryStudents, studentParams);

            while (sqlite3_step(db.stmt) == SQLITE_ROW)
            {
                string studentID = db.getQueryResult(0);
                checkUserInfo(studentID); // 调用 checkUserInfo 输出该房间住的人
            }
        } else
        {
            cout << "该房间无人入住。\n";
        }
    } else
    {
        cout << "未找到该房间。\n";
    }
}

void UserManager::deleteRoom(int dormitoryID)
{
    string roomNumber;

    // 提示管理员输入房间号
    cout << "请输入要删除的房间号: ";
    getline(cin, roomNumber);

    // 先检查该房间是否有学生入住
    checkRoomOccupancy(dormitoryID, roomNumber);

    // 提示是否删除该房间
    cout << "确认删除房间 " << roomNumber << " 吗？(yes/no): ";
    string confirm;
    cin >> confirm;

    if (confirm == "yes")
    {
        // 删除该房间
        string deleteRoomQuery = "DELETE FROM rooms WHERE dormitoryID = ? AND roomNumber = ?";
        db.executeWithParams(deleteRoomQuery, {to_string(dormitoryID), roomNumber});
        cout << "房间 " << roomNumber << " 已删除。\n";
    } else
    {
        cout << "取消删除房间。\n";
    }
}

void UserManager::deleteDormitory()
{
    string dormitoryName;
    cin.ignore(); // 清除输入缓存
    viewDormitories(); // 显示所有楼栋信息

    // 提示管理员输入楼栋名称
    cout << "请输入要删除的宿舍楼名称: " << endl;
    getline(cin, dormitoryName);

    // 查询楼栋是否存在
    string queryDormitory = "SELECT dormitoryID FROM dormitories WHERE name = '" + dormitoryName + "'";

    // 执行查询
    db.QueryExists(queryDormitory);

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

    db.QueryExists(queryRooms); // 执行查询房间ID

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

            db.QueryExists(queryRoomDetails);

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
                ViewStudentsInRoom(dormitoryName, roomNumber); // 打印住在该房间的学生信息
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


// // 如果有学生入住，提示是否继续删除楼栋
// if (hasStudents)
// {
//     cout << "宿舍楼有学生入住，确认删除楼栋吗？(yes/no): ";
//     string confirm;
//     cin >> confirm;
//
//     if (confirm == "yes")
//     {
//         // 删除该楼栋下的房间
//         string deleteRoomsQuery = "DELETE FROM rooms WHERE dormitoryID = ?";
//         db.executeWithParams(deleteRoomsQuery, {to_string(dormitoryID)});
//
//         // 删除楼栋
//         string deleteDormitoryQuery = "DELETE FROM dormitories WHERE dormitoryID = ?";
//         db.executeWithParams(deleteDormitoryQuery, {to_string(dormitoryID)});
//         cout << "楼栋 " << dormitoryName << " 已删除。\n";
//     } else
//     {
//         cout << "取消删除楼栋。\n";
//     }
// } else
// {
//     // 如果没有人入住，直接删除楼栋
//     string deleteRoomsQuery = "DELETE FROM rooms WHERE dormitoryID = ?";
//     db.executeWithParams(deleteRoomsQuery, {to_string(dormitoryID)});
//
//     string deleteDormitoryQuery = "DELETE FROM dormitories WHERE dormitoryID = ?";
//     db.executeWithParams(deleteDormitoryQuery, {to_string(dormitoryID)});
//     cout << "楼栋 " << dormitoryName << " 已删除。\n";
// }
//}


void UserManager::viewDormitories()
{
    // 构造SQL语句
    string sql = R"(
            SELECT d.name AS 宿舍楼,
                   d.sex AS 类型,
                   d.position AS 位置,
                   COUNT(r.roomID) AS 房间数,
                   SUM(r.capacity) AS 总容量,
                   SUM(r.occupied) AS 居住人数,
                   ROUND(SUM(r.occupied) * 100.0 / SUM(r.capacity), 2) AS 占用率
            FROM dormitories d
            LEFT JOIN rooms r ON d.dormitoryID = r.dormitoryID
            GROUP BY d.dormitoryID;
        )";

    // 执行SQL语句
    db.Query(sql);
}

void UserManager::ViewStudentsInRoom(const string &dormitoryName, const string &roomNumber)
{
    // 拼接查询语句，获取该房间中的所有学生姓名和ID
    string query = "SELECT u.name, u.userID "
                   "FROM users u "
                   "JOIN student_rooms sr ON u.userID = sr.studentID "
                   "JOIN rooms r ON sr.roomID = r.roomID "
                   "JOIN dormitories d ON r.dormitoryID = d.dormitoryID "
                   "WHERE d.name = '" + dormitoryName + "' AND r.roomNumber = '" + roomNumber + "';";

    // 存储学生的姓名和ID
    vector<pair<string, string> > students; // 每个元素是学生姓名和ID的组合

    // 执行查询
    db.QueryExists(query);

    // 遍历查询结果并将学生姓名和ID存储到数组中
    while (sqlite3_step(db.stmt) == SQLITE_ROW)
    {
        string studentName = db.getQueryResult(0); // 获取学生姓名
        string studentID = db.getQueryResult(1); // 获取学生ID
        students.push_back({studentName, studentID}); // 存储学生姓名和ID
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
