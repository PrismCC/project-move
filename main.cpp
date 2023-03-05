#include "structs.h"
#include "others.h"


inline map<int, cell> table;
inline map<char, int> trans;
inline map<int, Coordinate> jump;
inline map<int, Text> text;
inline map<int, NewMap> newMap;



int main()
{
    system("chcp 65001 > nul");

    cout << "This is project: move" << endl;
    bool first = true;

    string mapName;
    cout << "请输入加载的map文件名(不用输入\".txt\"):  ";
    cin >> mapName;
    cin.get();

    while (true)
    {
        fs::path mapPath{"map/" + mapName + ".txt"};
        ifstream mapIn{mapPath};


        if (mapIn.fail())
        {
            puts("无法打开该文件, 请检查是否输入正确及文件是否存在");
            cin.get();
            return 1;
        }
        {
            char check;
            mapIn >> check;
            if (check != '@')
            {
                puts("该文件不符合map文件规约");
                cin.get();
                return 1;
            }
        }
        cout << "加载地图成功" << endl;
        Sleep(500);
        clearScreen();

//***********************************************

        static int _x = 0, _y = 0;
        mapIn >> mapHeight >> mapWidth;
        {
            string temp;
            getline(mapIn, temp);
        }
        Map m(mapHeight, mapWidth);

//***********************************************

        string line;

        trans.insert({'0', 0});
        trans.insert({'1', 1});
        trans.insert({'2', 2});
        trans.insert({'@', 0});
        table.insert({0, {" ", 7, 0, 0}});
        table.insert({1, {"⊞", 7, 1, 0}});
        table.insert({2, {"⊠", 4, 2, 0}});
        while (true)
        {
            getline(mapIn, line);
            if (line.empty())
                continue;
            if (line[0] == '@')
                break;
            char c;
            int id, color, fun;
            string unicode;
            stringstream lineIn{line};
            lineIn >> c >> id >> unicode >> color >> fun;
            if (lineIn.fail())
            {
                cerr << "读入规则时出现错误\n";
                continue;
            }
            if (unicode == "`")
                unicode = " ";
            trans.insert({c, id});
            table.insert({id, {unicode, color, fun}});
        }

//***********************************************


        for (int i = 0; i < m.height; ++i)
            for (int j = 0; j < m.width; ++j)
            {
                char c;
                mapIn >> c;
                if (c == '\n')
                    mapIn >> c;
                if (c == '@' && first)
                {
                    _y = i;
                    _x = j;
                }
                m.data[i][j] = trans[c];
            }

//***********************************************

        vector<string> intro;
        while (mapIn.good())
        {
            getline(mapIn, line);
            if (line[0] == '<' && line[line.length() - 1] == '>')
            {
                string command = line.substr(1, line.length() - 2);
                if (command == "intro")
                {
                    do
                    {
                        getline(mapIn, line);
                        if (line.empty())
                            continue;
                        if (line[0] == '<' && line[line.length() - 1] == '>' &&
                            line.substr(1, line.length() - 2) == ("/" + command))
                            break;
                        intro.push_back(line);
                    } while (true);
                }
                if (command == "jump")
                {
                    do
                    {
                        getline(mapIn, line);
                        if (line.empty())
                            continue;
                        if (line[0] == '<' && line[line.length() - 1] == '>' &&
                            line.substr(1, line.length() - 2) == ("/" + command))
                            break;
                        stringstream lineIn{line};
                        int y1, y2, x1, x2 = -1;
                        lineIn >> y1 >> x1 >> y2 >> x2;
                        if (!lineIn.fail())
                            jump.insert({calCor(y1, x1), {y2, x2}});
                    } while (true);
                }
                if (command == "text")
                {
                    do
                    {
                        getline(mapIn, line);
                        if (line.empty())
                            continue;
                        if (line[0] == '<' && line[line.length() - 1] == '>' &&
                            line.substr(1, line.length() - 2) == ("/" + command))
                            break;
                        stringstream lineIn{line};
                        int color, y, x;
                        string content;
                        lineIn >> y >> x >> color >> content;
                        if (!lineIn.fail())
                            text.insert({calCor(y, x), {color, content}});
                    } while (true);
                }
                if (command == "newMap")
                {
                    do
                    {
                        getline(mapIn, line);
                        if (line.empty())
                            continue;
                        if (line[0] == '<' && line[line.length() - 1] == '>' &&
                            line.substr(1, line.length() - 2) == ("/" + command))
                            break;
                        stringstream lineIn{line};
                        int y1, x1, y2, x2;
                        string name;
                        lineIn >> y1 >> x1 >> y2 >> x2 >> name;
                        if (!lineIn.fail())
                            newMap.insert({calCor(y1, x1),
                                           {y2, x2, name}});
                    } while (true);
                }
            }
        }

//***********************************************



//***********************************************

        Player human(_x, _y, "❦");
        clearScreen();
        printScreen(m, human, mapName, intro);

//***********************************************

        while (true)
        {
            char key = 0;
            if (_kbhit())
                key = (char) getch();

            if (key != 0 && key != '`')
            {
                int ret;
                ret = human.move(key, m);
                if (ret == 5)
                {
                    if (newMap.find(human.yx().calCro()) != newMap.end())
                    {
                        loading();

                        mapName = newMap[human.yx().calCro()].name;
                        _x = newMap[human.yx().calCro()].x;
                        _y = newMap[human.yx().calCro()].y;
                        first = false;

                        table.clear();
                        trans.clear();
                        jump.clear();
                        text.clear();
                        newMap.clear();

                        break;
                    }
                }

                printScreen(m, human, mapName, intro);

            }

            if (key == '`')
                goto END;

            if (!human.isAlive())
                goto END;

            if (human.isWin())
            {
                textColor(6);
                cout << "Congratulations!!!" << endl;
                cin.get();
                return 0;
            }

            Sleep(20);

        }
    }
//***********************************************

    END:

    textColor(4);
    cout << "Game Over" << endl;
    textColor(7);
    cin.get();
    return 0;
}

