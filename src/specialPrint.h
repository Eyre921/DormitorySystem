//
// Created by CQL on 24-12-28.
//

#ifndef SPECIALPRINT_H
#define SPECIALPRINT_H

#include<bits/stdc++.h>
#include<windows.h>
#include<cstdlib>
using namespace std;


void gotoxy(int x, int y);

int randint_range(int n, int m);

void loading(const string &str, int width, int dash);

void SlowPrint(const string &str, int width, int align);

void MenuPrint(const string &str, int width);

void openPrint();

#endif //SPECIALPRINT_H
