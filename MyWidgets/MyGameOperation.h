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
#include <Qdebug>
class GameOperationWidget : public QWidget
{
    Q_OBJECT
private:

    QLCDNumber* LCD_Clue;
    QLCDNumber* LCD_Time;
    QPushButton* PushButton_Hard;
    QPushButton* PushButton_Pause;
    QPushButton* PushButton_Restart;
    QPushButton* PushButton_Back;
    QPushButton* PushButton_Forward;
    bool GamePause;
    int count;
    int hardness;
    QTimer* timer;
public:
    explicit GameOperationWidget(QWidget *parent = 0);

signals:
    void Game_Restart_Clicked(int);
    void Game_Pause_Clicked(bool);
    void Game_Back_Operation();
    void Game_Forward_Operation();
    void Game_AutoFill();
public slots:
    void Game_On_Restart_Clicked();
    void Game_On_Pause_Clicked();
    void Game_On_Timer();
    void Game_On_HardChanges();
    void Game_Clue_Show(int i);
    void Game_Finish();
    //0表示都不可以
    //1表示可后退不可向前
    //2表示可向前不可后退
    //3表示都可以
    void Game_Step_Update(int index);
};

#endif // GAMEOPERATIONWIDGET_H
