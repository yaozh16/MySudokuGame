#include "MyGridButtonWithBoard.h"

//菜单按键名称Board[1~9]
//按键上标签名Mark[1~9]
MyGridButtonWithBoardMenu::MyGridButtonWithBoardMenu(QWidget *parent) : QPushButton(parent)
{
    //状态和标记初始化
    States.clear();
    Marks.clear();
    for(int i=0;i<9;i++)
        States.push_back(false);
    //菜单设置
    menu=new QMenu;
    menu->setFixedSize(150,150);
    {
        QGridLayout* BoardLayout=new QGridLayout;
        //菜单键盘设置
        for(int y=1;y<4;y++)
            for(int x=1;x<4;x++)
            {
                QPushButton* btn=new QPushButton;
                btn->setObjectName("Board"+QString::number(x+y*3-3));
                btn->setFixedSize(50,50);
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
    setMenu(menu);
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
                BoardButtonLabelLayout->addWidget(marked,x,y,1,1);
            }
    }
    setLayout(BoardButtonLabelLayout);
}
void MyGridButtonWithBoardMenu::BoardButton_OnBoardClicked()
{

    QPushButton* btn=qobject_cast<QPushButton*>(sender());
    QString name=btn->objectName();
    name.remove(0,5);//去除Board关键字
    int index=name.toInt();//1~9
    qDebug()<<"--BoardButton_OnBoardClicked()..."<<index;
    if(Marks.find(0)==Marks.end())//非可动点，退出
        return ;
    States[index-1]=!(States[index-1]);
    if(States[index-1]==true)
        Marks.insert(index);
    else
        Marks.erase(index);
    emit BoardButton_ButtonSet(Marks);
    BoardButton_UpdateBoard(Marks);
}
void MyGridButtonWithBoardMenu::BoardButton_UpdateBoard(std::set<int> Marks_)
{
    //qDebug()<<"--BoardButton_UpdateBoard()...";
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
            //qDebug()<<"\t"<<i+1<<"Marked";
            States[i]=true;
            Marks.insert(i+1);
            lab->show();
        }
        else
        {
            //qDebug()<<"\t"<<i+1<<"Not Marked";
            States[i]=false;
            Marks.erase(i+1);
            lab->hide();
        }
    }
}
