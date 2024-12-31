//
// Created by CQL on 24-12-28.
//
#include "specialPrint.h"
using namespace std;

//无闪屏清屏
void clearScreen(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//产生n~m间的随机数（包括m和n）
int randIntRange(int n, int m)
{
    double base = static_cast<double>(rand()) / RAND_MAX;
    int res = base * static_cast<double>(m - n + 1) + n;
    return res;
}

//加载界面
void loading(const string &str, int width, int dash)
{
    int len = str.size();

    string tempSpace;
    for (int i = 1; i <= (width - len * 0.67) / 2; i++)
    {
        tempSpace += " ";
    }
    string Str = tempSpace + str + tempSpace;
    string tempDash = "+";
    for (int i = 1; i <= width - 2; i++)
    {
        tempDash += "-";
    }
    tempDash += "+";
    int full = width - 2;
    int index = 0;
    while (index <= full)
    {
        //		printf("%s\n",Str.c_str());
        //		printf("%s\n",tempDash.c_str());
        cout << Str << endl;
        cout << tempDash << endl;
        tempSpace = "";
        string tempStr;
        for (int i = 1; i <= index; i++)
        {
            tempStr += "#";
        }
        for (int i = 1; i <= full - index; i++)
        {
            tempSpace += " ";
        }
        //		printf("|%s%s|\n",tempStr.c_str(),tempSpace.c_str());
        //		printf("%s\n",tempDash.c_str());
        cout << "|" << tempStr << tempSpace << "|" << endl;
        cout << tempDash << endl;
        if (index == full)
        {
            Sleep(1000);
            break;
        }
        int step = randIntRange(1, 5);
        index += step;
        if (index < full)
        {
            Sleep(dash);
            clearScreen(0, 0);
        } else if (index >= full)
        {
            index = full;
            clearScreen(0, 0);
        }
    }
}

//缓慢打印
void slowPrint(const string &str, int width, int align)
{
    //align:对齐方式（-1为左对齐，0为居中对齐，1为右对齐）
    int len = str.size();
    string tempStr;
    string tempSpace;
    for (int i = 1; i <= (width - len * 0.66) / 2.0; i++)
    {
        tempSpace += " ";
    }
    if (align == -1)
    {
        tempStr = str;
    } else if (align == 0)
    {
        tempStr = tempSpace + str + tempSpace;
    } else if (align == 1)
    {
        tempStr = tempSpace + tempSpace + str;
    }
    for (char i: tempStr)
    {
        cout << i;
        Sleep(1);
    }
    if (align == 0 || align == 1)
    {
        cout << endl;
    }
}

//菜单打印
void menuPrint(const string &str, int width)
{
    if (str == "UP")
    {
        string tempDash;
        for (int i = 1; i <= width - 3; i++)
        {
            tempDash += "─";
        }
        string tempStr = "╭" + tempDash + "╮";
        cout << tempStr << endl;
    } else if (str == "DOWN")
    {
        string tempDash;
        for (int i = 1; i <= width - 3; i++)
        {
            tempDash += "─";
        }
        string tempStr = "╰" + tempDash + "╯";
        cout << tempStr << endl;
    } else
    {
        string tempStr = "[ " + str + " ]";
        string tempSpace;
        int len = tempStr.size();
        for (int i = 1; i <= (width - len * 0.67 - 2) / 2 - 1; i++)
        {
            tempSpace += " ";
        }
        tempStr = "│" + tempSpace + tempStr + tempSpace + "│";
        cout << tempStr << endl;
    }
    Sleep(10);
}

//启动开屏显示
void openPrint()
{
    cout << R"(
 __        __   _                            _
 \ \      / /__| | ___ ___  _ __ ___   ___  | |_ ___
  \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \
   \ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |
  __\_/\_/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/
 |  _ \  ___  _ __ _ __ ___ (_) |_ ___  _ __ _   _
 | | | |/ _ \| '__| '_ ` _ \| | __/ _ \| '__| | | |
 | |_| | (_) | |  | | | | | | | || (_) | |  | |_| |
 |____/ \___/|_|  |_| |_| |_|_|\__\___/|_|   \__, |           _
  _ __ ___   __ _ _ __   __ _  __ _  ___ _ __|___/  ___ _ __ | |_
 | '_ ` _ \ / _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|
 | | | | | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_
 |_| |_| |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|
  ___ _   _ ___| |_ ___ _ __ _|___/
 / __| | | / __| __/ _ \ '_ ` _ \
 \__ \ |_| \__ \ ||  __/ | | | | |
 |___/\__, |___/\__\___|_| |_| |_|
      |___/
	)";
    Sleep(1500);
}
