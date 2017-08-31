#pragma once
#include <stdlib.h>
#include <cstring>
#include <vector>
//#define My_Debug
#define MyQt
#define NewApproach


#ifdef My_Debug
#include <iostream>
#include <iomanip>
#include <string>
#endif


#ifdef MyQt
#include <QVector>
#endif

class MySudokuSolver
{
public:
    MySudokuSolver(){Init();}
    ~MySudokuSolver(){
        Grid.clear();
        filledGrid.clear();
        for(int i=0;i<FinalGrids.size();i++)
                FinalGrids[i].clear();
    }
    int importGrid(std::vector<int> Grid);
    int SolveWithSearch();
    int Search();
    std::vector<int> setClue(int number=30);
#ifdef My_Debug
    int Output(int *Grid_=NULL);
    int Output(bool *Grid);
#endif
private:
    int Check(std::vector<int> Grid);
    int Init();
    int ClueNumber(std::vector<int> Grid);
#ifdef My_Debug
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
         return 0;
 }
#endif
    int isSafe(int x,int y,int v);

    int SetGrid(int x,int y,int v);
#ifdef My_Debug
    int UpdateRow(int i)
    {
        int num;
        for(int v=0;v<9;v++)
        {
            num=0;
            for(int j=0;j<9;j++)
                if(!numGrid[v][i*9+j])
                    num+=1;
#ifdef My_Debug
            if(num!=numRecordRow[v][i])
            {
                std::cout<<"num("<<v+1<<")Row"<<i+1<<"failed:"<<num<<"!="<<numRecordRow[v][i]<<std::endl;
                PauseDebug();
            }
#endif
            numRecordRow[v][i]=num;
        }
        return 0;
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
#ifdef My_Debug
            if(num!=numRecordArray[v][i])
            {
                std::cout<<"num("<<v+1<<") Array "<<i+1<<" failed: "<<num<<" != "<<numRecordArray[v][i]<<std::endl;
                PauseDebug();
            }
#endif
            numRecordArray[v][i]=num;
        }
        return 0;

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
#ifdef My_Debug
            if(num!=numRecordBox[v][i])
            {
                std::cout<<"num("<<v+1<<")Box"<<i+1<<"failed:"<<num<<"!="<<numRecordBox[v][i]<<std::endl;
                PauseDebug();
            }
#endif
            numRecordBox[v][i]=num;
        }
        return 0;
    }
#endif
    int SearchRows();
    int SearchArrays();
    int SearchBoxes();
    int SearchRow(int r,int v);
    int SearchArray(int a,int v);
    int SearchBox(int b,int v);
    int GuessWithSearch(int xStart,int yStart);
    std::vector<int> RecordRow;
    std::vector<int> RecordArray;
    std::vector<int> RecordBox;
    std::vector<std::vector<int>> numRecordRow;
    std::vector<std::vector<int>> numRecordArray;
    std::vector<std::vector<int>> numRecordBox;
    std::vector<std::vector<bool>> numGrid;
    int GetBoxIndex(int x,int y);
    int GetBoxOffset(int &x,int &y,int index);
    std::vector<int> Grid;
    bool ChangeFlag;
    int clueNumber;
    std::vector<std::vector<int>> FinalGrids;
    int fillNumber;
    std::vector<int> filledGrid;
    friend class ParaState;
public:
    class ParaState
    {
    private:
        int pclueNumber;
        std::vector<int> pGrid;
        std::vector<int> pRecordRow;
        std::vector<int> pRecordArray;
        std::vector<int> pRecordBox;
        std::vector<std::vector<int>> pnumRecordRow;
        std::vector<std::vector<int>> pnumRecordArray;
        std::vector<std::vector<int>> pnumRecordBox;
        std::vector<std::vector<bool>> pnumGrid;
    public:
        int Save(MySudokuSolver* solver)
        {
            pclueNumber=solver->clueNumber;
            for(int i=0;i<81;i++)
                pGrid.push_back(solver->Grid[i]);
            for(int i=0;i<9;i++)
            {
                pRecordRow.push_back(solver->RecordRow[i]);
                pRecordArray.push_back(solver->RecordArray[i]);
                pRecordBox.push_back(solver->RecordBox[i]);
                std::vector<int> tr;
                std::vector<int> ta;
                std::vector<int> tb;
                for(int j=0;j<9;j++)
                {
                    tr.push_back(solver->numRecordRow[i][j]);
                    ta.push_back(solver->numRecordArray[i][j]);
                    tb.push_back(solver->numRecordBox[i][j]);
                }
                pnumRecordRow.push_back(tr);
                pnumRecordArray.push_back(ta);
                pnumRecordBox.push_back(tb);
                std::vector<bool> tnum;
                for(int j=0;j<81;j++)
                    tnum.push_back(solver->numGrid[i][j]);
                pnumGrid.push_back(tnum);
            }
            return 0;
        }
        int Load(MySudokuSolver* solver)
        {
            solver->numGrid.clear();
            solver->numRecordArray.clear();
            solver->numRecordBox.clear();
            solver->numRecordRow.clear();
            solver->RecordArray.clear();
            solver->RecordBox.clear();
            solver->RecordRow.clear();
            solver->Grid.clear();

            solver->clueNumber=pclueNumber;
            for(int i=0;i<81;i++)
                solver->Grid.push_back(pGrid[i]);
            for(int i=0;i<9;i++)
            {
                solver->RecordRow.push_back(pRecordRow[i]);
                solver->RecordArray.push_back(pRecordArray[i]);
                solver->RecordBox.push_back(pRecordBox[i]);
                std::vector<int> tr;
                std::vector<int> ta;
                std::vector<int> tb;
                for(int j=0;j<9;j++)
                {
                    tr.push_back(pnumRecordRow[i][j]);
                    ta.push_back(pnumRecordArray[i][j]);
                    tb.push_back(pnumRecordBox[i][j]);
                }
                solver->numRecordRow.push_back(tr);
                solver->numRecordArray.push_back(ta);
                solver->numRecordBox.push_back(tb);
                std::vector<bool> tnum;
                for(int j=0;j<81;j++)
                    tnum.push_back(pnumGrid[i][j]);
                solver->numGrid.push_back(tnum);
            }
            return 0;
        }
    };

};
