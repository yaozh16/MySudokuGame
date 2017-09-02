#ifndef MYDIFFICULTYEVALUATER_H
#define MYDIFFICULTYEVALUATER_H
#include "MySudokuSolver.h"
#include <vector>
class MyDifficultyEvaluater
{
public:
    MyDifficultyEvaluater();
    MySudokuSolver solver;
    void Init();
    int Evaluate();

};

#endif // MYDIFFICULTYEVALUATER_H
