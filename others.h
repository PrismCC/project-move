#ifndef MOVE_OTHERS_H
#define MOVE_OTHERS_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>

inline int mapWidth=1, mapHeight=1;

using namespace std;
namespace fs=std::filesystem;

void textColor(int color=7, int back = 0);
void clearScreen();
int calCor(int y,int x);
void loading();


#endif //MOVE_OTHERS_H
