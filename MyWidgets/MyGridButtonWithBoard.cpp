#include "MyGridButtonWithBoard.h"
#include <QMouseEvent>
//菜单按键名称Board[1~9]
//按键上标签名Mark[1~9]
MyGridButtonWithBoardMenu::MyGridButtonWithBoardMenu(QWidget *parent) :
    QPushButton(parent),
    menuOnFlag(false),
    PauseFlag(false),
    WorkingMode(0)
{
    //状态和标记初始化
    States.clear();
    Marks.clear();
    for(int i=0;i<9;i++)
        States.push_back(false);
    //菜单设置
    menu=new QMenu;
    {
        QGridLayout* BoardLayout=new QGridLayout;
        //菜单键盘设置
        for(int y=1;y<4;y++)
            for(int x=1;x<4;x++)
            {
                QPushButton* btn=new QPushButton;
                btn->setObjectName("Board"+QString::number(x+y*3-3));
                btn->setFixedSize(60,60);
                QString style;
                style+="QPushButton{";
                style+="border-image: url(:/resources/numbers/"+QString::number(x+y*3-3)+".jpg);";
                style+="border:1px solid white;";
                style+="border-radius:5px}";
                btn->setStyleSheet(style);
                connect(btn,SIGNAL(clicked(bool)),this,SLOT(BoardButton_OnBoardClicked()));
                BoardLayout->addWidget(btn,y,x,1,1);
            }
        QString style;
        style+="border:1px solid white;";
        style+="border-radius:5px";
        menu->setStyleSheet(style);
        menu->setLayout(BoardLayout);
    }
    connect(this,&QPushButton::clicked,this,BoardButton_ShowMenu);
    //键主体设置
    setFixedSize(60,60);
    QString style;
    style+="QPushButton{";
    style+="border-image: url(:/resources/numbers/0.jpg);";
    style+="border:1px solid white;";
    style+="border-radius:5px}";
    setStyleSheet(style);
    //按键上的布局
    QGridLayout* BoardButtonLabelLayout=new QGridLayout;
    {
        BoardButtonLabelLayout->setObjectName("BoardButtonLayout");
        for(int x=1;x<4;x++)
            for(int y=1;y<4;y++)
            {
                //标记
                QLabel* marked=new QLabel;
                marked->setObjectName("Mark"+QString::number(y+x*3-3));
                marked->setStyleSheet("border-image: url(:/resources/numbers/number"+QString::number(y+x*3-3)+".png);");
                marked->hide();
                Labels.push_back(marked);
                BoardButtonLabelLayout->addWidget(marked,x,y,1,1);
            }
    }
    setLayout(BoardButtonLabelLayout);
}
//获取按键当前按下的数字并且做状态记录
void MyGridButtonWithBoardMenu::BoardButton_OnBoardClicked()
{
    menuOnFlag=false;
    menu->close();
    QPushButton* btn=qobject_cast<QPushButton*>(sender());
    QString name=btn->objectName();
    name.remove(0,5);//去除Board关键字
    int index=name.toInt();//1~9
    qDebug()<<"--BoardButton_OnBoardClicked()..."<<index<<"..menuOnFlag="<<(menuOnFlag?"true":"false");
    if(Marks.find(0)==Marks.end())//非可动点，退出
        return ;
    States[index-1]=!(States[index-1]);
    if(States[index-1]==true)
        Marks.insert(index);
    else
        Marks.erase(index);
    emit BoardButton_ButtonSet(Marks,index);
    BoardButton_UpdateBoard(Marks);
}
void MyGridButtonWithBoardMenu::BoardButton_FakeBoardClicked(int index)
{
    if(PauseFlag)
        return;
    qDebug()<<"--BoardButton_FakeBoardClicked()..."<<index;
    if(Marks.find(0)==Marks.end())//非可动点，退出
        return ;
    States[index-1]=!(States[index-1]);
    if(States[index-1]==true)
        Marks.insert(index);
    else
        Marks.erase(index);
    emit BoardButton_ButtonSet(Marks,index);
    BoardButton_UpdateBoard(Marks);
}
void MyGridButtonWithBoardMenu::BoardButton_UpdateBoard(std::set<int> Marks_)
{
    if(PauseFlag)
        return;
    bool tembool=(Marks_.find(0)!=Marks_.end());
    if(tembool)
        Marks.insert(0);
    else
        Marks.erase(0);

    for(int i=0;i<9;i++)
    {
        QPushButton* btn=findChild<QPushButton*>("Board"+QString::number(i+1));
        QLabel* lab=findChild<QLabel*>("Mark"+QString::number(i+1));
        if(Marks_.find(i+1)!=Marks_.end())//存在
        {
            States[i]=true;
            Marks.insert(i+1);
            lab->show();
        }
        else
        {
            States[i]=false;
            Marks.erase(i+1);
            lab->hide();
        }
    }
}
void MyGridButtonWithBoardMenu::SetColor(QString pre)
{
    if(PauseFlag)
        return;
    QString style;
    style+="QPushButton{";
    style+="border-image: url(:/resources/numbers/";
    style+=pre;
    style+="0.jpg);";
    style+="border:1px solid white;";
    style+="border-radius:5px}";
    setStyleSheet(style);
}
void MyGridButtonWithBoardMenu::BoardButton_ShowMenu()
{
    if(PauseFlag)
        return;
    if(Marks.find(0)==Marks.end())//没有0
        return;
    if(WorkingMode==0)
        if(menuOnFlag)
        {
            menuOnFlag=false;
            menu->close();
        }
        else
        {
            menuOnFlag=true;
            menu->exec(mapToGlobal(QPoint(60,0)));
        }
    else
    {
        for(int i=0;i<9;i++)
           States[i]=false;
        States[WorkingMode-1]=true;
        Marks.clear();
        Marks.insert(0);
        Marks.insert(WorkingMode);
        emit BoardButton_ButtonSet(Marks,WorkingMode);
        BoardButton_UpdateBoard(Marks);
    }

}
void MyGridButtonWithBoardMenu::BoardButton_MarkFix(bool fix)
{
    if(PauseFlag)
        return;
    if(fix)
        Marks.erase(0);
    for(int index=1;index<10;index++)
    {
        //标记
        QLabel* marked=findChild<QLabel*>("Mark"+QString::number(index));
        if(fix)
            marked->setStyleSheet("border-image: url(:/resources/numbers/f"+QString::number(index)+".png);");
        else
            marked->setStyleSheet("border-image: url(:/resources/numbers/number"+QString::number(index)+".png);");
    }
    return;
}
void MyGridButtonWithBoardMenu::BoardButton_Pause(bool pauseFlag)
{
    if(PauseFlag!=pauseFlag)
    {
        PauseFlag=pauseFlag;
        if(PauseFlag)
            for(int i=0;i<9;i++)
                Labels[i]->hide();
        else
            for(int i=1;i<10;i++)
                if(Marks.find(i)==Marks.end())
                    Labels[i-1]->hide();
                else
                    Labels[i-1]->show();
    }
}
