#pragma once
#include <stdlib.h>
#include <cstring>

#define My_Debug
#define NewApproach
#define MyStepShow
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
    int SolveWithGuess(){Guess(1,1);}
    int SolveWithSearch(){GuessWithSearch(1,1);}
    int Search();
#ifdef My_Debug
    int Output();
#endif
private:
    int Init();

    bool isRowSafe(int x,int y,int v);
    bool isArraySafe(int x,int y,int v);
    bool isBoxSafe(int x,int y,int v);
    int GuessNotSafe(int x,int y,int v);

    int isSafe(int x,int y,int v);

    int SetGrid(int x,int y,int v);

    int SearchRows();
    int SearchArrays();
    int SearchBoxes();
    int SearchRow(int r,int v);
    int SearchArray(int a,int v);
    int SearchBox(int b,int v);
    int Guess(int xStart,int yStart);
    int GuessWithSearch(int xStart,int yStart);
    short RecordRow[9];
    short RecordArray[9];
    short RecordBox[9];
    short numRecordRow[9][9];
    short numRecordArray[9][9];
    short numRecordBox[9][9];
    int* Grid;
    int Count;
    bool ChangeFlag;
};
