#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QIcon>
#include <QLCDNumber>
#include <QVector>
#include <GameBase/MySudokuGenerater.h>
#include <GameBase/MySudokuSolver.h>
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
    //导入新的地图
    int Import(int clue=30);
    QVector<QString> Number;
    QVector<QVector<int>> MarkedNumbers;
    Ui::MainWindow *ui;
    QWidget *SudokuGridLayoutWidget;
    QWidget *SudokuOperationLayoutWidget;
    QWidget *GameOperationLayoutWidget;
    MySudokuGenerater generater;
    MySudokuSolver solver;
    QVector<int> Grid;
    int currentNumber;
    void SetGrid(int x, int y, int v,QString style="");
public slots:
    int Init();
    void OnGridClicked();
    void OnRestartClicked();
    void OnPauseClicked();
    void OnNumberClicked();
};

#endif // MAINWINDOW_H
