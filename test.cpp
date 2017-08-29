#include "MySudokuGenerater.h"
#include "MySudokuSolver.h"
#include <iostream>
int main()
{
    MySudokuGenerater generater;


    MySudokuSolver solver;
    solver.importGrid(generater.getGrid());
    solver.Search();
    solver.Output();
    std::cout<<"Done"<<std::endl;
}
