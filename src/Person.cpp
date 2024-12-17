#include "Person.h"

using namespace std;

Person::Person(const string& dbPath) {
    openDatabase(dbPath);
}

Person::~Person() {
    closeDatabase();
}

// 打开数据库
bool Person::openDatabase(const string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
        return false;
    } else {
        cout << "成功打开数据库!" << endl;
        return true;
    }
}

// 关闭数据库
void Person::closeDatabase() {
    sqlite3_close(db);
    cout << "数据库已关闭!" << endl;
}

// 增（Insert）操作
bool Person::insert(const string& name, int age) {
    const string insertSQL = "INSERT INTO users (name, age) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, age);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "插入数据失败: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    cout << "数据插入成功!" << endl;
    sqlite3_finalize(stmt);
    return true;
}

// 查（Select）操作
void Person::displayAll() {
    const string selectSQL = "SELECT * FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "查询结果：" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = (const char*)sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
    }

    sqlite3_finalize(stmt);
}

// 改（Update）操作
bool Person::update(const string& name, int age) {
    const string updateSQL = "UPDATE users SET age = ? WHERE name = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, updateSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, age);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "更新数据失败: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    cout << "数据更新成功!" << endl;
    sqlite3_finalize(stmt);
    return true;
}

// 删（Delete）操作
bool Person::remove(const string& name) {
    const string deleteSQL = "DELETE FROM users WHERE name = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, deleteSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "SQL语句编译失败: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "删除数据失败: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    cout << "数据删除成功!" << endl;
    sqlite3_finalize(stmt);
    return true;
}
