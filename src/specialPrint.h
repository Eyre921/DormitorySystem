//
// Created by CQL on 24-12-28.
//

#ifndef SPECIALPRINT_H
#define SPECIALPRINT_H

#include<bits/stdc++.h>
#include<windows.h>
#include<cstdlib>
using namespace std;


void clearScreen(int x, int y);

int randIntRange(int n, int m);

void loading(const string &str, int width, int dash);

void slowPrint(const string &str, int width, int align);

void menuPrint(const string &str, int width);

void openPrint();

#endif //SPECIALPRINT_H
