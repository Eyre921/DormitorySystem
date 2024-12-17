#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <sqlite3.h>
#include <string>

class Person {
public:
    Person(const std::string& dbPath);
    ~Person();

    bool insert(const std::string& name, int age);
    bool update(const std::string& name, int age);
    bool remove(const std::string& name);
    void displayAll();
    bool openDatabase(const std::string& dbPath);
    void closeDatabase();

private:
    sqlite3* db;
    char* errMsg;
};

#endif // PERSON_H
