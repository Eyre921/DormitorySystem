#include "Database.h"
#include <cstdlib>  // for system()

// 构造函数，打开数据库
Database::Database(const std::string &dbPath)
{
    if (sqlite3_open(dbPath.c_str(), &db))
    {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else
    {
        std::cout << "数据库连接成功！" << std::endl;
    }
}

// 析构函数，关闭数据库
Database::~Database()
{
    if (db)
    {
        sqlite3_close(db);
        std::cout << "数据库已关闭！" << std::endl;
    }
}

// 执行非查询 SQL（如 INSERT, UPDATE, DELETE）
bool Database::execute(const std::string &sql)
{
    if (db == nullptr)
    {
        std::cerr << "数据库未连接！" << std::endl;
        return false;
    }

    char *errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL 执行失败: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}


// 使用 sqlite3 命令行工具执行查询并格式化输出
bool Database::Query(const std::string &sql)
{
    if (db == nullptr)
    {
        std::cerr << "数据库未连接！" << std::endl;
        return false;
    }

    // 定义数据库文件路径
    std::string dbFile = "../data/dormitory.db"; // SQLite 数据库文件路径

    // 构造命令行指令
    std::string command = "sqlite3 -header -column " + dbFile + " \"" + sql + "\"";

    // 使用 system() 调用 sqlite3 命令行工具执行查询
    int result = system(command.c_str());

    // 判断命令执行是否成功
    if (result != 0)
    {
        std::cerr << "执行 SQL 查询失败！" << std::endl;
        return false;
    }

    return true;
}

bool Database::user_insert(const std::string &userID, const std::string &name, const std::string &gender,
                           const std::string &password, const std::string &contactInfo, int isCheckedIn, int isAdmin)
{
    // 构造 INSERT SQL 语句
    std::string sql = "INSERT INTO users (userID, name, gender, password, contactInfo, isCheckedIn, isAdmin) "
                      "VALUES ('" + userID + "', '" + name + "', '" + gender + "', '" + password + "', '" + contactInfo
                      + "', "
                      + std::to_string(isCheckedIn) + ", " + std::to_string(isAdmin) + ");";

    // 使用通用的 execute 执行插入操作
    return execute(sql);
}
