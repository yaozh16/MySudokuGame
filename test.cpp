#include "MySudokuGenerater.h"
#include "MySudokuSolver.h"
#include <iostream>
int main()
{
    MySudokuGenerater generater;
    MySudokuSolver solver;
    generater.Generate();
    solver.importGrid(generater.getGrid());
    solver.SolveWithSearch();
    std::cout<<"Done"<<std::endl;
}
