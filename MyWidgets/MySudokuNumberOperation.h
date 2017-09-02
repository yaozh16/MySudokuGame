#ifndef SUDOKUOPERATIONNUMBERWIDGET_H
#define SUDOKUOPERATIONNUMBERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
class SudokuOperationNumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuOperationNumberWidget(QWidget *parent = 0);
    QPushButton* PushButton_AutoStep;
signals:
    //是否把某个按键标出或者取消全部(0)
    void Number_SelectBroadCast(int i);
    void Number_AutoStep();
public slots:
};

#endif // SUDOKUOPERATIONNUMBERWIDGET_H
