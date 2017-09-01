#include "MySudokuGrid.h"
//按键名[行][列]
SudokuGridWidget::SudokuGridWidget(QWidget *parent) :
    QWidget(parent),
    Pause(false)
{
    QGridLayout* SudokuGridLayout=new QGridLayout;
    SudokuGridLayout->setSpacing(0);
    SudokuGridLayout->setContentsMargins(0,0,0,0);
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
        {
            QLabel* blocklabel=new QLabel;
            blocklabel->setFixedSize(188,188);
            QString style;
            style+="border:4px solid blue;";
            style+="border-radius:4px";
            blocklabel->setStyleSheet(style);
            SudokuGridLayout->addWidget(blocklabel,(i-1)*184,(j-1)*184,188,188);
        }
    for(int i=1;i<10;i++)
        for(int j=1;j<10;j++)
        {
            //按键
            MyGridButtonWithBoardMenu* button=new MyGridButtonWithBoardMenu;
            button->setObjectName(QString::number(i*10+j,10));
            //按键加入
            SudokuGridLayout->addWidget(button,(i+2)/3*4+(i-1)*60,(j+2)/3*4+(j-1)*60,60,60);
            //消息响应
            //左键
            connect(button,SIGNAL(BoardButton_ButtonSet(std::set<int>)),this,SLOT(Grid_OnChangeGridSet(std::set<int>)));
        }
    setLayout(SudokuGridLayout);
}

void SudokuGridWidget::Grid_Import(int clue)
{
    ImportFlag=true;
    Clue=0;
    GridNumbers.clear();
    qDebug()<<"Import...";
    MySudokuGenerater generater;
    MySudokuSolver solver;
    generater.Generate();
    solver.importGrid(generater.getGrid());

    std::vector<int> tem=solver.setClue(clue);
    for(int i=0;i<81;i++)
    {
        //保存每个位置的可能集合
        GridNumbers.push_back(tem[i]);
        std::set<int> t;
        t.insert(tem[i]);
        MyGridButtonWithBoardMenu* btn=findChild<MyGridButtonWithBoardMenu*>(QString::number((i/9+1)*10+i%9+1));
        btn->BoardButton_UpdateBoard(t);
        if (tem[i]!=0)
            Clue++;
    }
    qDebug()<<"--Import()...Done";
    Steps.clear();
    stepIndex=0;
    ImportFlag=false;
    return;
}

//保存全局地图
void SudokuGridWidget::Grid_OnChangeGridSet(std::set<int> set_)
{
    qDebug()<<"--Grid_OnChangeGridSet()...";
    MyGridButtonWithBoardMenu *btn=qobject_cast<MyGridButtonWithBoardMenu*>(sender());
    QString name=btn->objectName();
    int x=name.toInt()%10;
    int y=name.toInt()/10;
    if(!ImportFlag)
        if(Steps.size()==10)//满了
        {
            if(stepIndex==9)//正常进行
            {
                Steps.pop_front();
                Steps.push_back(Step(QPoint(x,y),set_));
            }
            else//正在后退
            {
                while(Steps.size()>stepIndex+1)
                    Steps.pop_back();
                stepIndex++;
            }
        }
        else//没满
        {
            Steps.push_back(Step(QPoint(x,y),set_));
            stepIndex++;
        }

    if(GridNumbers[x+y*9-10]!=0&&set_.size()!=1)//原本不为0的点现在填入了不止一个或者没有数字
        Clue--;
    if(set_.size()==1)//当前点只有一个
    {
        if(GridNumbers[x+y*9-10]==0)
            Clue++;
        GridNumbers[x+y*9-10]=*(set_.begin());
    }
    if(!ImportFlag)
        qDebug()<<"\tClue is now: "<<Clue;
}

void SudokuGridWidget::Grid_Pause(bool show)
{
    Pause!=Pause;
    qDebug()<<"Pause "<<(show?"true":"false");
}
void SudokuGridWidget::Grid_Forward()
{
    if(stepIndex+1<Steps.size())
    {
        stepIndex++;
        qDebug()<<"--Grid_Forward():"<<stepIndex;
    }

}
void SudokuGridWidget::Grid_Back()
{
    if(stepIndex>0)
    {
        stepIndex--;
        qDebug()<<"--Grid_Forward():"<<stepIndex;
    }
}
