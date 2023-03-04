#include "structs.h"

extern map<int,cell> table;
extern map<int,Coordinate> jump;
extern map<int,Text> text;
extern map<int,NewMap> newMap;


int Player::move(char c, const Map &m)
{
    if (state != 0)
        return false;
    int gy, gx;
    switch (c)
    {
        case 'w':
            gy = y - 1;
            gx = x;
            break;
        case 's':
            gy = y + 1;
            gx = x;
            break;
        case 'a':
            gy = y;
            gx = x - 1;
            break;
        case 'd':
            gy = y;
            gx = x + 1;
            break;
        default:
            return false;
    }
    if (gx >= 0 && gx < m.width && gy >= 0 && gy < m.height)
    {
        int id=m.data[gy][gx];
        switch (table[id].pFun)
        {
            case 0:
                y = gy;
                x = gx;
                return 0;
            case 1:
                return 1;
            case 2:
                y = gy;
                x = gx;
                state = 2;
                return 2;
            case 3:
                y = gy;
                x = gx;
                state = 3;
                return 3;
            case 4:
                y=jump[calCor(gy,gx)].y;
                x=jump[calCor(gy,gx)].x;
                return 4;
            case 5:
                y = gy;
                x = gx;
                return 5;
            case 6:
                y = gy;
                x = gx;
                return 6;
            default:
                break;
        }
    }
    return false;
}

void Player::say() const
{
    if(text.find(calCor(y,x))!=text.end())
    {
        textColor(text[calCor(y,x)].color);
        cout<<text[calCor(y,x)].content<<endl;
        textColor(7);
    }
    else
        puts("");
}

void Map::print(Player &p) const
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (p.isAlive() && p.match(i, j))
            {
                textColor(13);
                cout << p.print();
                continue;
            }

            int id=data[i][j];
            textColor(table[id].color);
            cout<<table[id].unicode;
        }
        textColor(7);
        putchar('\n');
    }
}

void printScreen(Map &m, Player &human,string &mapName,vector<string> &intro)
{
    clearScreen();
    textColor(11);
    cout << "Map: " << mapName << "  height:" << m.height << "  " << "width:" << m.width << endl;
    textColor(8);
    cout << "--------------------------------------------" << endl;
    textColor(7);
    m.print(human);
    textColor(8);
    cout << "--------------------------------------------" << endl;
    textColor(11);
    cout << "当前坐标: " << human.coordinate() << endl << endl;
    textColor(8);
    cout << "--------------------------------------------" << endl;
    textColor(9);
    for (auto &x: intro)
        cout << x << endl;
    textColor(8);
    cout << "--------------------------------------------" << endl;
    human.say();
    textColor(8);
    cout << "--------------------------------------------" << endl;
}