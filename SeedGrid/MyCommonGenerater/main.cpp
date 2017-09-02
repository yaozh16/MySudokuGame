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

    while(1)
    {
        generater.Generate();
        solver.importGrid(generater.getGrid());
        solver.SolveWithSearch();
        generater.Print(solver.setClue(81));
        system("pause");
    }
    return 0;
}
