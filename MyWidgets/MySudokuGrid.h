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
    MySudokuGenerater generater;
    MySudokuSolver solver;
    std::vector<int> FinalGrid;

    std::vector<MyGridButtonWithBoardMenu*> Buttons;

    struct Step
    {
        QPoint point;
        int num;
        Step(QPoint p, int Number):point(p),num(Number){;}
    };
    std::deque<Step> Steps;
    int stepIndex;

    int Clue;
    int ImportFlag;

    int selectNumber;//选中的数字
    int DesignMode;
    void Grid_CompleteCheck();
    bool FakeClick;
    bool Pause;
    bool stepDirectionForward;

signals:
    void Grid_Clue_Broadcast(int clue);
    void Grid_Finished();
    //0表示都不行,1表示可后退不可向前,2表示可向前不可后退,3表示都可以
    void Grid_Step_State(int i);
    void Grid_Button_Pause(bool pauseFlag);
public slots:
    void Grid_OnChangeGridSet(std::set<int> set_, int v);
    void Grid_Import(int hardness=1);
    void Grid_Pause(bool pauseFlag);
    void Grid_Forward();
    void Grid_Back();
    void Grid_Select(int i);//选择
    void Grid_AutoStep();//自动走步
    void Grid_SetDesignMode(int mode);
    void Grid_DesignGo();
    void Grid_ReInit();

};

#endif // SUDOKUGRIDWIDGET_H
