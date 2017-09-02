#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <set>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>
#include <QVector>
#include <MyWidgets/MyGameOperation.h>
#include <MyWidgets/MySudokuGrid.h>
#include <MyWidgets/MySudokuNumberOperation.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVector<QString> Number;
    Ui::MainWindow *ui;
    SudokuGridWidget *My_Sudoku_Grid_Widget;
    SudokuOperationNumberWidget *My_Sudoku_Number_Widget;
    GameOperationWidget *My_Game_Operation_Widget;
    int Init();
public slots:

};

#endif // MAINWINDOW_H
