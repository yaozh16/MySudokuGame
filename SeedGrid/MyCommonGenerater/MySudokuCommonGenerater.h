#pragma once
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
#include <vector>

#include <iostream>
#include <iomanip>





class MySudokuGenerater
{
public:
    MySudokuGenerater(){MySudokuGenerater::Init();}
    ~MySudokuGenerater(){if(Grid.size()>0) Grid.clear();}
    int Generate();
    std::vector<int> getGrid();
    void Import(std::vector<int> newGrid);
    void SaveSeed(int i);
    int Print(std::vector<int> grid);
    int SeedGrid();
private:
    int Init();
    int Safe(int index, int v);
    int DFSfill();
    int towerSwap();
    int floorSwap();
    int arraySwap();
    int rowSwap();
    int NumberReplace();
    std::vector<int> Grid;
    void swap(int &x,int&y);
};

