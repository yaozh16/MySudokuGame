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
#include <string>
#endif
class MySudokuSolver
{
public:
    MySudokuSolver(){Init();}
    ~MySudokuSolver(){
        if(Grid)
            delete Grid;
        if(filledGrid)
            delete filledGrid;
        if(FinalGrids.size()>0)
            for(auto iter:FinalGrids)
                delete &(*(iter));
    }
    int importGrid(int* Grid);
    int SolveWithSearch();
    int Search();
    int* setClue(int number);
#ifdef My_Debug
    int Output(int *Grid_=NULL);
    int Output(bool *Grid);
#endif
private:
    int Check(int *Grid);
    int Init();
    int ClueNumber(int *Grid);
    int GuessNotSafe(int x,int y,int v);
    int PauseDebug()
 {
         int tem;
         while(1)
         {
             std::cout<<">>";
             std::cin>>tem;
             if(tem==-1)
                 Output();
             else if(tem>0&&tem<10)
                 Output(numGrid[tem-1]);
             else
                 break;
         }
 }
    int isRowSafe(int x,int y,int v);
    int isArraySafe(int x,int y,int v);
    int isBoxSafe(int x,int y,int v);
    int isSafe(int x,int y,int v);

    int SetGrid(int x,int y,int v);

    int UpdateRow(int i)
    {
        int num;
        for(int v=0;v<9;v++)
        {
            num=0;
            for(int j=0;j<9;j++)
                if(!numGrid[v][i*9+j])
                    num+=1;
            if(num!=numRecordRow[v][i])
            {
                std::cout<<"num("<<v+1<<")Row"<<i+1<<"failed:"<<num<<"!="<<numRecordRow[v][i]<<std::endl;
                PauseDebug();
            }
            numRecordRow[v][i]=num;
        }

    }
    int UpdateArray(int i)
    {
        int num;
        for(int v=0;v<9;v++)
        {
            num=0;
            for(int j=0;j<9;j++)
                if(!numGrid[v][i+j*9])
                    num+=1;
            if(num!=numRecordArray[v][i])
            {
                std::cout<<"num("<<v+1<<") Array "<<i+1<<" failed: "<<num<<" != "<<numRecordArray[v][i]<<std::endl;
                PauseDebug();
            }
            numRecordArray[v][i]=num;
        }

    }
    int UpdateBox(int i)
    {
        int num;
        int x,y;
        GetBoxOffset(x,y,i);
        for(int v=0;v<9;v++)
        {
            num=0;
            int index=x+y*9-20;
            for(int j=0;j<3;j++)
            {
                index+=9;
                for(int k=0;k<3;k++)
                {
                    index+=1;
                    if(!numGrid[v][index])
                    num+=1;
                }
                index-=3;
            }
            if(num!=numRecordBox[v][i])
            {
                std::cout<<"num("<<v+1<<")Box"<<i+1<<"failed:"<<num<<"!="<<numRecordBox[v][i]<<std::endl;
                PauseDebug();
            }
            numRecordBox[v][i]=num;
        }

    }

    int SearchRows();
    int SearchArrays();
    int SearchBoxes();
    int SearchRow(int r,int v);
    int SearchArray(int a,int v);
    int SearchBox(int b,int v);
    int GuessWithSearch(int xStart,int yStart);
    int RecordRow[9];
    int RecordArray[9];
    int RecordBox[9];
    int numRecordRow[9][9];
    int numRecordArray[9][9];
    int numRecordBox[9][9];
    bool numGrid[9][81];
    int GetBoxIndex(int x,int y);
    int GetBoxOffset(int &x,int &y,int index);
    int* Grid;
    bool ChangeFlag;
    int clueNumber;
    std::vector<int*> FinalGrids;
    int fillNumber;
    int *filledGrid;
    friend class ParaState;
public:
    class ParaState
    {
    private:
        int pclueNumber;
        bool pnumGrid[9][81];
        int pGrid[81];
        int pRecordRow[9];
        int pRecordArray[9];
        int pRecordBox[9];
        int pnumRecordRow[9][9];
        int pnumRecordArray[9][9];
        int pnumRecordBox[9][9];
    public:
        int Save(MySudokuSolver* solver)
        {
            pclueNumber=solver->clueNumber;
            for(int i=0;i<81;i++)
                pGrid[i]=solver->Grid[i];
            for(int i=0;i<9;i++)
            {
                pRecordRow[i]=solver->RecordRow[i];
                pRecordArray[i]=solver->RecordArray[i];
                pRecordBox[i]=solver->RecordBox[i];
                for(int j=0;j<9;j++)
                {
                    pnumRecordRow[i][j]=solver->numRecordRow[i][j];
                    pnumRecordArray[i][j]=solver->numRecordArray[i][j];
                    pnumRecordBox[i][j]=solver->numRecordBox[i][j];
                }
                for(int j=0;j<81;j++)
                    pnumGrid[i][j]=solver->numGrid[i][j];
            }
            return 0;
        }
        int Load(MySudokuSolver* solver)
        {
            solver->clueNumber=pclueNumber;
            for(int i=0;i<81;i++)
                solver->Grid[i]=pGrid[i];
            for(int i=0;i<9;i++)
            {
                solver->RecordRow[i]=pRecordRow[i];
                solver->RecordArray[i]=pRecordArray[i];
                solver->RecordBox[i]=pRecordBox[i];
                for(int j=0;j<9;j++)
                {
                    solver->numRecordRow[i][j]=pnumRecordRow[i][j];
                    solver->numRecordArray[i][j]=pnumRecordArray[i][j];
                    solver->numRecordBox[i][j]=pnumRecordBox[i][j];
                }
                for(int j=0;j<81;j++)
                    solver->numGrid[i][j]=pnumGrid[i][j];
            }
            return 0;
        }
    };

};
