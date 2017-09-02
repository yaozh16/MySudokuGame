#include <iostream>
#include "MySudokuCommonGenerater.h"
#include "MySudokuSolver.h"
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    MySudokuGenerater generater;
    generater.SeedGrid();
    generater.Print(generater.getGrid());
    MySudokuSolver solver;

    std::vector<int> t=generater.getGrid();
    generater.Print(t);
    while(1)
    {
        int x,y,v;
        solver.importGrid(t);
        std::cout<<"Solution="<<solver.SolveWithSearch()<<endl;
        std::cout<<"First Guess="<<solver.getGuessCount0()<<endl;
        std::cout<<"input x y v:";
        std::cin>>x>>y>>v;
        t[x+9*y-10]=v;
    }
    return 0;
}
