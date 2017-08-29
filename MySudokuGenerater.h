#pragma once
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
#define My_Debug

#ifdef My_Debug
#include <iostream>
#include <iomanip>
#endif

class MySudokuGenerater
{
public:
    MySudokuGenerater(){Init();}
    ~MySudokuGenerater(){if(Grid) delete Grid;}
    int Generate();
    int* getGrid();
    int Print();
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

