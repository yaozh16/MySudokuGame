#ifndef GAMEOPERATIONWIDGET_H
#define GAMEOPERATIONWIDGET_H
#include <QLCDNumber>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QMenu>
class GameOperationWidget : public QWidget
{
    Q_OBJECT
private:
    bool GamePause;
    int count;
    int clue;
    QTimer* timer;
public:
    explicit GameOperationWidget(QWidget *parent = 0);

signals:
    void Game_Restart_Clicked(int);
    void Game_Pause_Clicked(bool);
    void Game_Back_Operation();
    void Game_Forward_Operation();
public slots:
    void Game_On_Restart_Clicked();
    void Game_On_Pause_Clicked();
    void Game_On_Timer();
    void Game_On_HardChanges();
};

#endif // GAMEOPERATIONWIDGET_H
