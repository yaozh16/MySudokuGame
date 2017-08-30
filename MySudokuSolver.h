#pragma once
#include <stdlib.h>
#include <cstring>
#include <vector>
#define My_Debug
#define NewApproach
//#define MyStepShow
#ifdef My_Debug
#include <iostream>
#include <iomanip>
#endif
class MySudokuSolver
{
public:
    MySudokuSolver(){Init();}
    ~MySudokuSolver(){if(Grid) delete Grid;}
    int importGrid(int* Grid);
    int SolveWithSearch();
    int Search();
    int setClue(int number);
#ifdef My_Debug
    int Output(int *Grid_=NULL);
    int OutputFillGrid();
#endif
private:
    int Init();
    int ClueNumber(int *Grid);
    int GuessNotSafe(int x,int y,int v);

    int isSafe(int x,int y,int v);

    int SetGrid(int x,int y,int v);

    int SearchRows();
    int SearchArrays();
    int SearchBoxes();
    int SearchRow(int r,int v);
    int SearchArray(int a,int v);
    int SearchBox(int b,int v);
    int GuessWithSearch(int xStart,int yStart);
    short RecordRow[9];
    short RecordArray[9];
    short RecordBox[9];
    short numRecordRow[9][9];
    short numRecordArray[9][9];
    short numRecordBox[9][9];
    int* Grid;
    bool ChangeFlag;
    std::vector<int*> FinalGrids;
    int fillNumber;
    int *filledGrid;
};
