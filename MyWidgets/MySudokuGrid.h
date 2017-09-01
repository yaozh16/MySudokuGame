#ifndef SUDOKUGRIDWIDGET_H
#define SUDOKUGRIDWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPoint>
#include <set>
#include <vector>
#include <deque>
#include <GameBase/MySudokuGenerater.h>
#include <GameBase/MySudokuSolver.h>
#include <MyWidgets/MyGridButtonWithBoard.h>

class SudokuGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuGridWidget(QWidget *parent = 0);
    std::vector<int> GridNumbers;
private:
    struct Step
    {
        QPoint point;
        std::set<int> set;
        Step(QPoint p, std::set<int> s):point(p),set(s){;}
    };
    std::deque<Step> Steps;
    int stepIndex;
    int Clue;
    bool ImportFlag;
    bool Pause;
    int Check();
signals:

public slots:
    void Grid_OnChangeGridSet(std::set<int> set_);
    void Grid_Import(int clue=17);
    void Grid_Pause(bool show);
    void Grid_Forward();
    void Grid_Back();
};

#endif // SUDOKUGRIDWIDGET_H
