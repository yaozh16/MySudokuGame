#include "MyGameOperation.h"

GameOperationWidget::GameOperationWidget(QWidget *parent) :
    QWidget(parent),
    GamePause(false)
{
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GameOperationWidget::Game_On_Timer);
    QGridLayout* GameOperationLayout=new QGridLayout;
    //Restart按钮
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Restart");
        btn->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/restart1.png);";
        style+="border:5px solid green;";
        style+="border-radius:3px}";
        btn->setFlat(true);
        btn->setStyleSheet(style);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(Game_On_Restart_Clicked()));
        GameOperationLayout->addWidget(btn,1,1,1,1);
    }
    //Pause按钮
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Pause");
        btn->setFixedSize(50,50);
        QString style;
        style+="QPushButton#Pause{";
        style+="border-image: url(:/resources/pause.png);";
        style+="border:5px solid green;";
        style+="border-radius:3px}";
        btn->setFlat(true);
        btn->setStyleSheet(style);

        connect(btn,SIGNAL(clicked(bool)),this,SLOT(Game_On_Pause_Clicked()));
        GameOperationLayout->addWidget(btn,1,2,1,1);
    }
    //Back按钮
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Back");
        btn->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/Cancel1.png);";
        style+="border:5px solid green;";
        style+="border-radius:3px}";
        btn->setFlat(true);
        btn->setStyleSheet(style);
        GameOperationLayout->addWidget(btn,1,3,1,1);
        connect(btn,&QPushButton::clicked,this,[&](){emit Game_Back_Operation();});
    }
    //Forward按钮
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Forward");
        btn->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/Go1.png);";
        style+="border:5px solid green;";
        style+="border-radius:3px}";
        btn->setFlat(true);
        btn->setStyleSheet(style);
        GameOperationLayout->addWidget(btn,1,4,1,1);
        connect(btn,&QPushButton::clicked,this,[&](){emit Game_Forward_Operation();});
    }
    //难度按钮
    {
        QPushButton* hard=new QPushButton;
        hard->setObjectName("HardButton");
        hard->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/numbers/n1.png);";
        style+="border:5px solid green;";
        style+="border-radius:25px}";
        hard->setFlat(true);
        hard->setStyleSheet(style);
        clue=17;
        QMenu* menu=new QMenu;
        for(int i=1;i<10;i++)
        {
            QAction* action=new QAction(this);
            action->setText(QString::number(i));
            action->setObjectName("Hard"+QString::number(i));
            connect(action,SIGNAL(triggered(bool)),this,SLOT(Game_On_HardChanges()));
            menu->addAction(action);
        }
        hard->setMenu(menu);
        GameOperationLayout->addWidget(hard,1,5,1,1);
    }
    //LCDTimer显示器
    {
        QLCDNumber* Number=new QLCDNumber(this);
        Number->setObjectName("LCDTimer");
        Number->setDigitCount(5);
        Number->setSegmentStyle(QLCDNumber::Filled);
        Number->display("00:00");
        GameOperationLayout->addWidget(Number,1,6,2,1);
    }
    setLayout(GameOperationLayout);
}
void GameOperationWidget::Game_On_Restart_Clicked()
{
    timer->stop();
    timer->blockSignals(false);
    count=0;
    timer->start(1000);
    emit Game_Restart_Clicked(clue);
}
void GameOperationWidget::Game_On_Pause_Clicked()
{
    GamePause=!GamePause;
    timer->blockSignals(GamePause);
    emit Game_Pause_Clicked(GamePause);
}
void GameOperationWidget::Game_On_Timer()
{
    QTime time;
    count++;
    time.setHMS(0,0,count,0);
    QString text=time.toString("mm:ss");
    if((time.second()%2)==0)
        text[2]=' ';
    findChild<QLCDNumber*>("LCDTimer")->display(text);
}
void GameOperationWidget::Game_On_HardChanges()
{
    QAction* ac=qobject_cast<QAction*>(sender());
    QString name=ac->objectName();
    name.remove(0,4);//去除"Hard"
    int hard=name.toInt();
    clue=62-hard*5;
    findChild<QPushButton*>("HardButton")->setStyleSheet("border-image: url(:/resources/numbers/n"+name+".png);");
    Game_On_Restart_Clicked();
}
