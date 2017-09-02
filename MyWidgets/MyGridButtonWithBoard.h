#ifndef MYGRIDBOARDMENU_H
#define MYGRIDBOARDMENU_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <set>
#include <QDebug>
#include <QPoint>
#include <QVector>
class MyGridButtonWithBoardMenu : public QPushButton
{
    Q_OBJECT
public:
    std::vector<bool> States;
    std::set<int> Marks;
    QVector<QLabel*> Labels;
    explicit MyGridButtonWithBoardMenu(QWidget *parent = 0);
    void BoardButton_UpdateBoard(std::set<int> Marks_);
    void BoardButton_FakeBoardClicked(int index);
    void SetColor(QString pre="");
    void BoardButton_MarkFix(bool fix);
private:
    QMenu* menu;
    bool menuOnFlag;
    bool PauseFlag;
signals:
    //发送该按钮当前已经被Mark的数字集合
    void BoardButton_ButtonSet(std::set<int> s, int v);
public slots:
    //菜单选中
    void BoardButton_OnBoardClicked();
    void BoardButton_ShowMenu();
    void BoardButton_Pause(bool pauseFlag);
};

#endif // MYGRIDBOARDMENU_H
