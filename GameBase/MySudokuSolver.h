#pragma once
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <deque>
#define NewApproach




class MySudokuSolver
{
public:
    MySudokuSolver(){Init();}
    ~MySudokuSolver()
    {
        Grid.clear();
        filledGrid.clear();
        FinalGuessCounts.clear();
        FinalGrids.clear();
    }
    int importGrid(std::vector<int> Grid);
    int SolveWithSearch();
    int Search();
    int ClueNumber(std::vector<int> Grid);

    std::vector<int> setClue(int number=30);
    std::vector<int> getGrid(){return Grid;}
    std::vector<int> getFinalGrid0()
    {
        if(FinalGrids.size()>0)
            return *(FinalGrids.begin());
        else
        {
           std::vector<int> t;
           for(int i=0;i<81;i++)
               t.push_back(0);
           return t;
        }
    }
    int getGuessCount0()
    {
        if(FinalGuessCounts.size()>0)
            return FinalGuessCounts[0];
        else
            return -1;
    }
    std::vector<std::vector<int>> getFinalGrids(){return FinalGrids;}
    std::vector<int> getGuessCounts(){return FinalGuessCounts;}
    std::vector<int> getLeastAndMostDepth()
    {
        std::deque<int> t;
        t.push_back(81);
        t.push_back(-1);
        for(int i=0;i<FinalGuessCounts.size();i++)
        {
            if(FinalGuessCounts[i]<t[0])
                t[0]=FinalGuessCounts[i];
            if(FinalGuessCounts[i]>t[1])
                t[1]=FinalGuessCounts[i];
        }
        std::vector<int> tp;
        tp.push_back(t[0]);
        tp.push_back(t[1]);
        return tp;
    }
    int isSafe(int x,int y,int v);
    std::vector<std::vector<bool>> numGrid;

private:
    int Check(std::vector<int> Grid);
    int Init();

    int SetGrid(int x,int y,int v);

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

    int GetBoxIndex(int x,int y);
    int GetBoxOffset(int &x,int &y,int index);
    std::vector<int> Grid;
    bool ChangeFlag;
    int clueNumber;
    std::vector<std::vector<int>> FinalGrids;
    std::vector<int> FinalGuessCounts;
    int GuessCount;
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
            pGrid=solver->Grid;
            pRecordRow=solver->RecordRow;
            pRecordArray=solver->RecordArray;
            pRecordBox=solver->RecordBox;
            pnumRecordRow=solver->numRecordRow;
            pnumRecordArray=solver->numRecordArray;
            pnumRecordBox=solver->numRecordBox;
            pnumGrid=solver->numGrid;
            return 0;
        }
        int Load(MySudokuSolver* solver)
        {
            solver->numGrid=pnumGrid;
            solver->numRecordArray=pnumRecordArray;
            solver->numRecordBox=pnumRecordBox;
            solver->numRecordRow=pnumRecordRow;
            solver->RecordArray=pRecordArray;
            solver->RecordBox=pRecordBox;
            solver->RecordRow=pRecordRow;
            solver->Grid=pGrid;
            solver->clueNumber=pclueNumber;
            return 0;
        }
    };
#ifdef My_Debug
    int Output(std::vector<int> Grid);
    int Output(std::vector<bool> Grid);
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
            if(num!=numRecordArray[v][i])
            {
                std::cout<<"num("<<v+1<<") Array "<<i+1<<" failed: "<<num<<" != "<<numRecordArray[v][i]<<std::endl;
                PauseDebug();
            }
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
            if(num!=numRecordBox[v][i])
            {
                std::cout<<"num("<<v+1<<")Box"<<i+1<<"failed:"<<num<<"!="<<numRecordBox[v][i]<<std::endl;
                PauseDebug();
            }
            numRecordBox[v][i]=num;
        }
        return 0;
    }
    int PauseDebug()
 {
         int tem;
         while(1)
         {
             std::cout<<">>";
             std::cin>>tem;
             if(tem==-1)
                 Output(Grid);
             else if(tem>0&&tem<10)
                 Output(numGrid[tem-1]);
             else
                 break;
         }
         return 0;
 }
#endif
};
