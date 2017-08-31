#pragma once
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
#include <vector>
//#define My_Debug
#define MyQt

#ifdef My_Debug
#include <iostream>
#include <iomanip>
#endif




class MySudokuGenerater
{
public:
    MySudokuGenerater(){MySudokuGenerater::Init();}
    ~MySudokuGenerater(){if(Grid.size()>0) Grid.clear();}
    int Generate();
    std::vector<int> getGrid();
    int Print();
private:
    int Init();
    int SeedGrid();
    int towerSwap();
    int floorSwap();
    int arraySwap();
    int rowSwap();
    int NumberReplace();
    std::vector<int> Grid;
    void swap(int &x,int&y);
};

