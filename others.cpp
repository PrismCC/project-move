#include "others.h"
#include "structs.h"

extern map<int,cell> table;
extern map<char,int> trans;




void textColor(int color, int back) // 更改控制台字色
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(output, color | (back % 16) * 16);
}
//0 黑
//1 深蓝 a
//2 绿 b
//3 青 c
//4 红 d
//5 紫 e
//6 黄 f
//7 白 g
//8 灰 h
//9 蓝 i
//10 嫩绿 j
//11 浅青 k
//12 橙 l
//13 粉红 m
//14 亮黄 n
//15 黄白 o


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