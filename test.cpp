#include "GameBase/MySudokuGenerater.h"
#include "GameBase/MySudokuSolver.h"
#include <iostream>
int main()
{
    /*std::vector<std::vector<int>> mi;
    std::vector<int> i;
    i.push_back(10);
    i.push_back(20);
    mi.push_back(i);
    mi[0][0]=6;
    i[1]-=1;
    for(int p=0;p<i.size();p++)
        std::cout<<i[p]<<std::endl;
    for(int p=0;p<mi.size();p++)
        for(int q=0;q<mi[p].size();q++)
            std::cout<<mi[p][q]<<std::endl;*/
    MySudokuGenerater generater;
    MySudokuSolver solver;
    generater.Generate();
    std::cout<<"Done1"<<std::endl;
    solver.importGrid(generater.getGrid());
    //solver.SolveWithSearch();
    solver.Output(solver.setClue(30));
    std::cout<<"Done"<<std::endl;
}
