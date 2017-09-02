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
        PushButton_Restart=new QPushButton;
        PushButton_Restart->setObjectName("Restart");
        PushButton_Restart->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/operation/GoOn.png);}";
        PushButton_Restart->setFlat(true);
        PushButton_Restart->setStyleSheet(style);
        connect(PushButton_Restart,SIGNAL(clicked(bool)),this,SLOT(Game_On_Restart_Clicked()));
        GameOperationLayout->addWidget(PushButton_Restart,1,3,1,1);
    }
    //Pause按钮
    {
        PushButton_Pause=new QPushButton;
        PushButton_Pause->setObjectName("Pause");
        PushButton_Pause->setFixedSize(50,50);
        QString style;
        style+="QPushButton#Pause{";
        style+="border-image: url(:/resources/operation/Pause.png);}";
        PushButton_Pause->setFlat(true);
        PushButton_Pause->setStyleSheet(style);
        PushButton_Pause->hide();
        connect(PushButton_Pause,SIGNAL(clicked(bool)),this,SLOT(Game_On_Pause_Clicked()));
        GameOperationLayout->addWidget(PushButton_Pause,1,4,1,1);
    }
    //Back按钮
    {
        PushButton_Back=new QPushButton;
        PushButton_Back->setObjectName("Back");
        PushButton_Back->setFixedSize(50,50);
        PushButton_Back->setFlat(true);
        PushButton_Back->setStyleSheet("QPushButton{border-image: url(:/resources/operation/NBack.png);}");
        GameOperationLayout->addWidget(PushButton_Back,1,5,1,1);
        connect(PushButton_Back,&QPushButton::clicked,this,[&](){emit Game_Back_Operation();});
    }
    //Forward按钮
    {
        PushButton_Forward=new QPushButton;
        PushButton_Forward->setObjectName("Forward");
        PushButton_Forward->setFixedSize(50,50);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/operation/NForward.png);}";
        PushButton_Forward->setFlat(true);
        PushButton_Forward->setStyleSheet(style);
        GameOperationLayout->addWidget(PushButton_Forward,1,6,1,1);
        connect(PushButton_Forward,&QPushButton::clicked,this,[&](){emit Game_Forward_Operation();});
    }
    //难度按钮
    {
        PushButton_Hard=new QPushButton;
        PushButton_Hard->setObjectName("PushButton_Hard");
        PushButton_Hard->setFixedSize(60,60);
        QString style;
        style+="QPushButton{";
        style+="border-image: url(:/resources/numbers/n1.png);}";
        PushButton_Hard->setFlat(true);
        PushButton_Hard->setStyleSheet(style);
        hardness=1;
        QMenu* menu=new QMenu;
        menu->setObjectName("HardMenu");
        QGridLayout* Hardmenulayout=new QGridLayout;
        menu->setLayout(Hardmenulayout);
        for(int i=1;i<11;i++)
        {
            QPushButton* hardbutton=new QPushButton(PushButton_Hard);
            hardbutton->setStyleSheet("border-image: url(:/resources/numbers/n"+QString::number(i)+".png);}");
            hardbutton->setObjectName("Hard"+QString::number(i));
            hardbutton->setFixedSize(40,40);
            connect(hardbutton,SIGNAL(clicked(bool)),this,SLOT(Game_On_HardChanges()));
            Hardmenulayout->addWidget(hardbutton,i,1,1,1);
        }
        PushButton_Hard->setMenu(menu);
        GameOperationLayout->addWidget(PushButton_Hard,1,7,1,1);
    }
    //LCDTimer显示器
    {
        LCD_Time=new QLCDNumber(this);
        LCD_Time->setObjectName("LCD_Time");
        LCD_Time->setDigitCount(5);
        LCD_Time->setSegmentStyle(QLCDNumber::Filled);
        LCD_Time->display("00:00");
        GameOperationLayout->addWidget(LCD_Time,1,1,1,2);
    }
    //已经填写的Clue数目
    {
        LCD_Clue=new QLCDNumber(this);
        LCD_Clue->setObjectName("LCD_Clue");
        LCD_Clue->setDigitCount(2);
        LCD_Clue->display("0");
        GameOperationLayout->addWidget(LCD_Clue,1,8,1,1);
    }
    setLayout(GameOperationLayout);
}
void GameOperationWidget::Game_On_Restart_Clicked()
{
    PushButton_Pause->setStyleSheet("QPushButton{border-image: url(:/resources/operation/Pause.png);}");
    PushButton_Pause->show();
    timer->stop();
    timer->blockSignals(false);
    count=0;
    PushButton_Restart->setStyleSheet("QPushButton{border-image: url(:/resources/operation/Restart.png);}");
    timer->start(1000);
    emit Game_Restart_Clicked(hardness);
}
void GameOperationWidget::Game_On_Pause_Clicked()
{
    GamePause=!GamePause;
    if(GamePause)
        PushButton_Pause->setStyleSheet("QPushButton{border-image: url(:/resources/operation/GoOn.png);}");
    else
        PushButton_Pause->setStyleSheet("QPushButton{border-image: url(:/resources/operation/Pause.png);}");
    qDebug()<<"--Game_On_Pause_Clicked()..."<<(GamePause?"true":"false");
    timer->blockSignals(GamePause);
    emit Game_Pause_Clicked(GamePause);
}
void GameOperationWidget::Game_On_Timer()
{
    QTime time;
    count++;
    time.setHMS(0,count/60,count%60,0);
    QString text=time.toString("mm:ss");
    if((time.second()%2)==0)
        text[2]=' ';
    LCD_Time->display(text);
}
void GameOperationWidget::Game_On_HardChanges()
{

    QPushButton* ac=qobject_cast<QPushButton*>(sender());
    QString name=ac->objectName();
    name.remove(0,4);//去除"Hard"
    hardness=name.toInt();
    qDebug()<<"--Game_On_HardChanges()...Hard="<<hardness;
    PushButton_Hard->setStyleSheet("border-image: url(:/resources/numbers/n"+name+".png);");
    Game_On_Restart_Clicked();
}
void GameOperationWidget::Game_Clue_Show(int i)
{
    LCD_Clue->display(QString::number(i));
}
void GameOperationWidget::Game_Finish()
{
    timer->stop();
}
void GameOperationWidget::Game_Step_Update(int index)
{
    if (index==1||index==3)
        PushButton_Back->setStyleSheet("QPushButton{border-image: url(:/resources/operation/Back.png);}");
    else
        PushButton_Back->setStyleSheet("QPushButton{border-image: url(:/resources/operation/NBack.png);}");
    if (index==2||index==3)
        PushButton_Forward->setStyleSheet("QPushButton{border-image: url(:/resources/operation/Forward.png);}");
    else
        PushButton_Forward->setStyleSheet("QPushButton{border-image: url(:/resources/operation/NForward.png);}");

}
