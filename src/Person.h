#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <sqlite3.h>
#include <string>
using namespace std;
class Person {
public:
    Person(const string& dbPath);
    ~Person();

    bool insert(const string& name, int age);
    bool update(const string& name, int age);
    bool remove(const string& name);
    void displayAll();
    bool openDatabase(const string& dbPath);
    void closeDatabase();

private:
    sqlite3* db;
    char* errMsg;
};

#endif // PERSON_H
