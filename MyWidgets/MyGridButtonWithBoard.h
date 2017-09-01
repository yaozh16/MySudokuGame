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
class MyGridButtonWithBoardMenu : public QPushButton
{
    Q_OBJECT
public:

    std::vector<bool> States;
    std::set<int> Marks;
    explicit MyGridButtonWithBoardMenu(QWidget *parent = 0);
    void BoardButton_UpdateBoard(std::set<int> Marks_);
private:
    QMenu* menu;

signals:
    //发送该按钮当前已经被Mark的数字集合
    void BoardButton_ButtonSet(std::set<int> s);
public slots:
    //菜单选中
    void BoardButton_OnBoardClicked();

};

#endif // MYGRIDBOARDMENU_H
