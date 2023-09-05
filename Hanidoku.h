#pragma once
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<QDebug>
#include"SAT_solve_yh.h"

using namespace std;
const int zya = 0;

class Hanidoku {
public:
    int map[9][9];   //地图
    int ansmap[9][9]; //答案地图
    SAT_solver_yh* hanidoku_solve;

    int step_stack[100];
    int top_step_stack = -1;


    Hanidoku() {
        memset(map, 0, sizeof map);
        memset(ansmap, 0, sizeof ansmap);
    }

    //createmap使用提供的地图文件生成初始地图 mode为模式参数 xh为地图编号
    //easy地图有5190 hard地图有1050
    void createmap(int mode,int xh) {
        ifstream ifs;

       ifs.open("./resource/map_hanidoku/easy_hanidoku.txt", ios::in);


        if (!ifs.is_open())
        {
            cout << "文件打开失败！" << endl;
            return;
        }

        char mapdata[1024];
        for (int i = 1; i < xh; i++)ifs.getline(mapdata, sizeof(mapdata));
        ifs.getline(mapdata, sizeof(mapdata));

        int k = 5;
        for (int len = 5,i=0; len <= 9; len++,i++)
        {
            //i为层数
            for (int j = 0; j <= len-1; j++)
            {
                map[i][j] = mapdata[k++] - '0';
            }
        }

        for (int len = 8,i=5; len >= 5; len--,i++)
        {
            for (int j = 9 - len; j <= 8; j++)map[i][j] = mapdata[k++] - '0';
        }

        
        
        ifs.close();
        return;
    }


    



    pair<int,int> getlr(int i, int j)//根据坐标返回第几行第几个
    {
        if (i <= 4)return{ i+1,j+1 };
        else if (i > 4)
        {
            return { i+1,j - i + 5 };
        }
        return { -1,-1 };
    }
    pair<int, int> getij(int l, int r)//根据第几行第几个返回坐标
    {
        if (l <= 5)
        {
            return { l - 1,r - 1 };
        }
        else if (l > 5)
        {
            return{ l - 1,r + l - 6 };
        }
        return { 0,0 };
    }
    //生成空地图初始的约束条件cnf文件

    void Turntocnf(int mode,int xh)
    {
        hanidoku_solve = new SAT_solver_yh;
        hanidoku_solve->createfromfile(); //从cnfinit读取空地图的约束条件
        qDebug()<<"hereeee\n";
        createmap(mode,xh); //根据用户选择的难度和序号读取地图文件并创建初始地图
        hanidoku_solve->addcnf(map);//根据初始数据增加约束条

        hanidoku_solve->solve(1);

        getansmap(hanidoku_solve->ans);

        delete hanidoku_solve;
        return;
    }

    void getansmap(int* fzb)
    {
        for (int i = 0; i <= 4; i++)  //前五行
        {
            for (int j = 0; j <= 4 + i; j++)
            {
                pair<int, int> k = getlr(i, j);
                int loc = k.first * 100 + k.second * 10;
                bool a = false;
                for (int p = loc + 1; p <= loc + 9; p++)
                {
                    if (fzb[p - 110] == -1)continue;
                    if (!a && fzb[p - 110] == 1)
                    {
                        ansmap[i][j] = p % 10;
                        a = true;
                    }
                    else if (a && fzb[p - 110] == 1)
                    {
                        cout << "p=" << p << endl;
                        cout << "答案有误" << endl;
                        return;
                    }
                }
                if (!a)
                {
                    cout << "loc=" << loc;
                    cout << "答案有误" << endl;
                    return;
                }
            }
        }

        for (int i = 5; i <= 8; i++)  //后四行












        {
            for (int j = i-4; j <= 8; j++)
            {
                pair<int, int> k = getlr(i, j);
                int loc = k.first * 100 + k.second * 10;
                bool a = false;
                for (int p = loc + 1; p <= loc + 9; p++)
                {
                    if (fzb[p - 110] == -1)continue;
                    if (!a && fzb[p - 110] == 1)
                    {
                        ansmap[i][j] = p % 10;
                        a = true;
                    }
                    else if (a && fzb[p - 110] == 1)
                    {
                        cout << "p=" << p << endl;
                        cout << "答案有误" << endl;
                        return;
                    }
                }
                if (!a)
                {
                    cout << "loc=" << loc;
                    cout << "答案有误" << endl;
                    return;
                }
            }
        }
        return;
    }



    bool checkinput(int i, int j, int q)
    {
        pair<int, int> k = getij(i, j);
        if (map[k.first][k.second] != 0)return false;
        if (!(q >= 1 && q <= 9))return false;
        if (!(i >= 1 && i <= 9))return false;
        if ((i == 1 || i == 9) && !(j >= 1 && j <= 5))return false;
        if ((i == 2 || i == 8) && !(j >= 1 && j <= 6))return false;
        if ((i == 3 || i == 4) && !(j >= 1 && j <= 7))return false;
        if (i==5 && !(j >= 1 && j <= 9))return false;
        return true;
    }

    void input(int i, int j, int q)
    {
        pair<int, int> k = getij(i, j);
        map[k.first][k.second] = q;
        step_stack[++top_step_stack] = k.first * 100 + k.second * 10;
    }

    void output()
    {
        if (top_step_stack == -1)
        {
            cout << "已经没有上一步了！";
            return;
        }
        int k = step_stack[top_step_stack--];
        map[k / 100][(k % 100) / 10] = 0;
        cout << "已撤回！\n";
        getchar();
        getchar();
        return;
    }

    bool checkcurrentmap()
    {
        for (int i = 0; i <= 4; i++)  //前五行
        {
            for (int j = 0; j <= 4 + i; j++)
            {
                if (map[i][j] == 0)continue;
                if (map[i][j] != ansmap[i][j])return false;
            }
        }

        for (int i = 5; i <= 8; i++)  //后四行
        {
            for (int j = i - 4; j <= 8; j++)
            {
                if (map[i][j] == 0)continue;
                if (map[i][j] != ansmap[i][j])return false;
            }
        }
        return true;
    }

    };
