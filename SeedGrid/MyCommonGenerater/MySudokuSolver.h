#pragma once
#include <stdlib.h>
#include <cstring>
#include <vector>
#define NewApproach



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
    std::vector<int> getGrid(){return Grid;}
    std::vector<int> getFinalGrid0(){return *(FinalGrids.begin());}
    int isSafe(int x,int y,int v);
    std::vector<std::vector<bool>> numGrid;
private:
    int Check(std::vector<int> Grid);
    int Init();
    int ClueNumber(std::vector<int> Grid);



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
};
