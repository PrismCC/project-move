#include "others.h"
#include "structs.h"

extern map<int,cell> table;
extern map<char,int> trans;


void textColor(int color, int back) //0黑 1深蓝 2绿 3青 4红 5紫 6黄 7白 8灰 9蓝 10嫩绿 11浅青 12橙 13粉红 14亮黄 15黄白
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(output, color | (back % 16) * 16);
}


void clearScreen()// 清屏
{
    printf("\033[2J"); // 清屏
    printf("\033[0;0H"); // 光标移动到左上角
}

int calCor(int y,int x)
{
    return y * mapWidth + x;
}

void loading()
{
    clearScreen();
    textColor(13);
    cout << "少女祈祷中";
    Sleep(300);
    cout << ".";
    Sleep(300);
    cout << ".";
    Sleep(300);
    cout << ".";
    Sleep(300);
    textColor(7);
    clearScreen();
}