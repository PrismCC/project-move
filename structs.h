#ifndef MOVE_STRUCTS_H
#define MOVE_STRUCTS_H

#include "others.h"

struct Player;
struct Map;
struct cell;
struct Coordinate;
struct Text;
struct NewMap;

struct cell
{
    string unicode;
    int color;
    int pFun;
    [[maybe_unused]] int aFun;
};

struct Coordinate
{
    int y;
    int x;

    Coordinate() = default;

    Coordinate(int _y, int _x) : x(_x), y(_y) {}

    bool operator<(Coordinate a) const
    {
        if (y < a.y)
            return true;
        else
            return x < a.x;
    }

    [[nodiscard]] int calCro() const { return y * mapWidth + x; }
};

struct Text
{
    int color;
    string content;
};

struct NewMap
{
    int y;
    int x;
    string name;
};


class Player
{
private:
    int y;
    int x;
    int state;
    string unicode;
public:
    Player(int _x, int _y, const char *s) : x(_x), y(_y), state(0), unicode(s) {};

    [[nodiscard]] bool isAlive() const { return state != 2; }

    [[nodiscard]] bool isWin() const { return state == 3; }

    int move(char c, const Map &m);

    void say() const;

    [[nodiscard]] Coordinate yx() const { return {y, x}; }

    string &print() { return unicode; }

    [[nodiscard]] bool match(int _y, int _x) const { return _y == y && _x == x; }

    [[nodiscard]] string coordinate() const
    {
        char s[100];
        sprintf(s, "(%d,%d)", y, x);
        return s;
    }
};

struct Map
{
    int height;
    int width;
    int **data;

    Map(int h, int w)
    {
        height = h;
        width = w;
        data = new int *[height];
        for (int i = 0; i < h; ++i)
            data[i] = new int[width];
    }

    ~Map()
    {
        for (int i = 0; i < height; ++i)
            delete[] data[i];
        delete[] data;
    }

    void print(Player &p) const;
};

void printScreen(Map &m, Player &human,string &mapName,vector<string> &intro);

#endif //MOVE_STRUCTS_H
