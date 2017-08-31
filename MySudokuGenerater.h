#pragma once
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
//#define My_Debug
#define MyQt

#ifdef My_Debug
#include <iostream>
#include <iomanip>
#endif


#ifdef MyQt
#include <QVector>
#endif


class MySudokuGenerater
{
public:
    MySudokuGenerater(){MySudokuGenerater::Init();}
    ~MySudokuGenerater(){if(Grid) delete Grid;}
    int Generate();
    int* getGrid();
    int Print();
#ifdef MyQt
    QVector<int> getGridQt()
    {
        QVector<int> tem;
        for(int i=0;i<81;i++)
            tem.push_back(Grid[i]);
        return tem;
    }
#endif
private:
    int Init();
    int SeedGrid();
    int towerSwap();
    int floorSwap();
    int arraySwap();
    int rowSwap();
    int NumberReplace();
    int* Grid;
    int swap(int &x,int&y);
};

