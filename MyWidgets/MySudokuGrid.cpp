#include "MySudokuGrid.h"
#include <iostream>
#include <random>
#include <time.h>
#include <QMessageBox>
//按键名[行][列]
SudokuGridWidget::SudokuGridWidget(QWidget *parent) :
    QWidget(parent),
    Pause(false),
    selectNumber(0),
    ImportFlag(0),
    FakeClick(false),
    stepIndex(-1),
    stepDirectionForward(true),
    DesignMode(0)
{
    srand(time(NULL));
    Buttons.clear();
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
            connect(button,SIGNAL(BoardButton_ButtonSet(std::set<int>,int)),this,SLOT(Grid_OnChangeGridSet(std::set<int>,int)));
            connect(this,SIGNAL(Grid_Button_Pause(bool)),button,SLOT(BoardButton_Pause(bool)));
            Buttons.push_back(button);
        }
    setLayout(SudokuGridLayout);
}

void SudokuGridWidget::Grid_Import(int hardness)
{
    if(DesignMode!=0)
        return;
    FakeClick=false;
    selectNumber=0;
    ImportFlag=1;
    Clue=0;
    GridNumbers.clear();
    int setclue=77-hardness*6;
    qDebug()<<"--Grid_Import()...Set Clue to:"<<setclue;
    generater.Generate();
    solver.importGrid(generater.getGrid());

    GridNumbers=solver.setClue(setclue);
    if(GridNumbers.size()!=81)
        return;
    FinalGrid.clear();
    FinalGrid=solver.getFinalGrid0();
    for(int i=0;i<81;i++)
    {
        //保存每个位置的可能集合
        std::set<int> t;
        t.insert(GridNumbers[i]);
        Buttons[i]->BoardButton_UpdateBoard(t);
        if (GridNumbers[i]!=0)
        {
            Buttons[i]->BoardButton_MarkFix(true);
            Clue++;
        }
        else
            Buttons[i]->BoardButton_MarkFix(false);
    }
    qDebug()<<"--Import()...Done";
    emit Grid_Clue_Broadcast(Clue);
    emit Grid_Step_State(0);
    Steps.clear();
    stepIndex=-1;
    ImportFlag=2;
    Grid_Select(0);
    return;
}

//保存全局地图GridNumbers
//保存步骤step
//保存clue
void SudokuGridWidget::Grid_OnChangeGridSet(std::set<int> set_,int v)
{
    qDebug()<<"--Grid_OnChangeGridSet()...";
    MyGridButtonWithBoardMenu *btn=qobject_cast<MyGridButtonWithBoardMenu*>(sender());
    QString name=btn->objectName();
    int x=name.toInt()%10;
    int y=name.toInt()/10;
    if(ImportFlag==2)
        //Steps步骤保存
        if(FakeClick==false)//正常点击
        {
            if(Steps.size()==10)//满了
            {
                if(stepIndex==9)//正常进行
                {
                    Steps.pop_front();
                }
                else//中途
                {
                    while(Steps.size()>stepIndex+1)
                        Steps.pop_back();//去掉尾部
                    if(!stepDirectionForward)
                        Steps.pop_back();
                    else
                        stepIndex+=1;
                }
                Steps.push_back(Step(QPoint(x,y),v));
            }
            else//没满
            {
                while(Steps.size()>stepIndex+1)
                    Steps.pop_back();//去掉尾部
                if(!stepDirectionForward)
                    Steps.pop_back();
                else
                    stepIndex+=1;
                Steps.push_back(Step(QPoint(x,y),v));
            }
            stepDirectionForward=true;
            emit Grid_Step_State(1);
        }
        else
            FakeClick=false;
    //原来不为0，现在是设为2+或者是0
    if(GridNumbers[x+y*9-10]!=0&&set_.size()!=2)//原本不为0的点现在填入了不止一个或者没有数字
    {
        Clue-=1;
        GridNumbers[x+y*9-10]=0;
        qDebug()<<"\tClue is now: "<<Clue;
    }
    if(set_.size()==2)//当前点只有一个
    {
        if(GridNumbers[x+y*9-10]==0)//空白点填入
        {
            Clue++;
            GridNumbers[x+y*9-10]=*(set_.rbegin());
            Grid_CompleteCheck();
        }
        else
            GridNumbers[x+y*9-10]=*(set_.rbegin());
    }
    if(ImportFlag==2)
        qDebug()<<"\tClue is now: "<<Clue;

    emit Grid_Clue_Broadcast(Clue);
}

void SudokuGridWidget::Grid_Pause(bool pauseFlag)
{
    if(DesignMode!=0)
        return;
    Pause=pauseFlag;
    qDebug()<<"Pause "<<(pauseFlag?"true":"false");
    emit Grid_Button_Pause(Pause);
}
void SudokuGridWidget::Grid_Forward()
{
    if(DesignMode!=0)
        return;
    if(Pause)
        return;
    if(stepIndex+1<Steps.size())
    {
        if(stepDirectionForward)
            stepIndex+=1;
        qDebug()<<"--Grid_Forward():"<<stepIndex;
        Step t=Steps[stepIndex];
        FakeClick=true;
        MyGridButtonWithBoardMenu* btn=Buttons[t.point.x()+t.point.y()*9-10];
        btn->BoardButton_FakeBoardClicked(t.num);
        //此时相当于增加了Steps[stepIndex]一步
    }
    if(stepIndex+1==Steps.size())
        emit Grid_Step_State(1);
    else
        emit Grid_Step_State(3);
    stepDirectionForward=true;
}
void SudokuGridWidget::Grid_Back()
{
    if(DesignMode!=0)
        return;
    if(Pause)
        return;
    if(stepIndex>0)
    {
        if(!stepDirectionForward)
            stepIndex-=1;
        qDebug()<<"--Grid_Back():"<<stepIndex;
        Step t=Steps[stepIndex];
        FakeClick=true;
        MyGridButtonWithBoardMenu* btn=Buttons[t.point.x()+t.point.y()*9-10];
        btn->BoardButton_FakeBoardClicked(t.num);
    }
    if(stepIndex==0)
        emit Grid_Step_State(2);
    else
        emit Grid_Step_State(3);
    stepDirectionForward=false;
}
void SudokuGridWidget::Grid_CompleteCheck()
{
    if(DesignMode!=0)
        return;
    if(Clue==81)
    {
        bool Safeflag=true;

        for(int i=0;i<81;i++)
        {
            int v=GridNumbers[i];
            int x=i%9;
            int y=i/9;
            for(int j=0;j<9;j++)
            {
                if(j!=x&&GridNumbers[y*9+j]==v)
                {
                    Safeflag=false;
                    break;
                }
                if(j!=y&&GridNumbers[j*9+x]==v)
                {
                    Safeflag=false;
                    break;
                }
                int BIndex=x/3*3+y/3*27+j/3*9+j%3;
                if(BIndex!=i&&GridNumbers[BIndex]==v)//同Box
                {
                    Safeflag=false;
                    break;
                }
            }
            if(!Safeflag)//不安全
                break;
        }
        if(Safeflag)
        {
            qDebug()<<"Win!"<<endl;
            emit Grid_Finished();
            QMessageBox* box=new QMessageBox(this);
            box->setWindowIconText("Great!");
            box->setText("You Win!");
            box->setWindowIcon(QIcon(":/resources/others/SudokuGame.jpg"));
            box->show();
        }
        else
        {
            qDebug()<<"Fail!"<<endl;
            QMessageBox* box=new QMessageBox(this);
            box->setWindowIconText("Sorry!");
            box->setText("Please Check Again!");
            box->setWindowIcon(QIcon(":/resources/others/SudokuGame.jpg"));
            box->show();
        }
    }
}
void SudokuGridWidget::Grid_Select(int v)
{
    if(DesignMode!=0)
        return;
    if(Pause)
        return;
    if(ImportFlag<2)
        return;
    qDebug()<<"--Grid_Select("<<v<<")";
    if(v==0||v==selectNumber)//回复原状
    {
        selectNumber=0;
        for(int i=0;i<81;i++)
        {
            MyGridButtonWithBoardMenu* btn=Buttons[i];
            btn->SetColor("");
            btn->BoardButton_SetWorkingMode(0);
        }
    }
    else//选中某个数字
    {
        for(int i=0;i<81;i++)
        {
            MyGridButtonWithBoardMenu* btn=Buttons[i];
            btn->BoardButton_SetWorkingMode(v);
            if(GridNumbers[i]==v)//该点恰好为同数字点
            {
                btn->SetColor(QString("ss"));
            }
            else//
            {
                int x=i%9;
                int y=i/9;
                bool Safeflag=true;
                for(int j=0;j<9;j++)
                {
                    if(GridNumbers[y*9+j]==v||GridNumbers[j*9+x]==v||GridNumbers[x/3*3+y/3*27+j/3*9+j%3]==v)//同Box
                    {
                        Safeflag=false;
                        break;
                    }
                }
                if(Safeflag)//安全
                {
                    btn->SetColor("");
                }
                else//该点不安全
                    btn->SetColor("s");
            }

        }
        selectNumber=v;
    }

}
void SudokuGridWidget::Grid_AutoStep()
{
    if(DesignMode!=0)
        return;
    if(Pause)
        return;
    srand(time(NULL));
    if(ImportFlag<2)
        return;
    if(Clue==81)
        return;
    while(1)
    {
        int index=rand()%81;
        MyGridButtonWithBoardMenu* btn=Buttons[index];
        if(btn->Marks.find(0)!=btn->Marks.end())//可以动的点
            if((btn->Marks.size()!=2)                         //原来是空的或有多个标记
             ||(*(btn->Marks.rbegin())!=FinalGrid[index]))//只有一个点但是不是正确的数
            {
                qDebug("--Grid_AutoStep()...Point(%d,%d) to %d",index%9+1,index/9+1,FinalGrid[index]);
                std::set<int> t;
                t.insert(FinalGrid[index]);
                Buttons[index]->BoardButton_UpdateBoard(t);
                if (GridNumbers[index]==0)
                    Clue++;
                GridNumbers[index]=FinalGrid[index];
                emit Grid_Clue_Broadcast(Clue);
                Grid_CompleteCheck();
                break;
            }
    }
    return;
}
void SudokuGridWidget::Grid_SetDesignMode(int mode)
{
    if(DesignMode==mode)
        return ;
    qDebug()<<"--Grid_SetDesignMode("<<mode<<")";
    Grid_ReInit();
    DesignMode=mode;
    if(mode==1)
        for(int i=0;i<81;i++)
            Buttons[i]->BoardButton_SetWorkingMode(10);
    else
        for(int i=0;i<81;i++)
            (Buttons[i])->BoardButton_SetWorkingMode(0);

}
void SudokuGridWidget::Grid_ReInit()
{
    FinalGrid.clear();
    Pause=false;
    selectNumber=0;
    ImportFlag=0;
    FakeClick=false;
    stepIndex=-1;
    stepDirectionForward=true;
    GridNumbers.clear();
    Clue=0;
    Steps.clear();
    for(int i=0;i<81;i++)
    {
        GridNumbers.push_back(0);
        MyGridButtonWithBoardMenu* btn=Buttons[i];
        btn->BoardButton_ReInit();
    }
    qDebug()<<"--Grid_ReInit()...Done";
}
void SudokuGridWidget::Grid_DesignGo()
{
    qDebug()<<"--Grid_DesignGo()...Trying to solve...";
    solver.importGrid(GridNumbers);
    int t=solver.SolveWithSearch();
     qDebug()<<"\tSolve...Done";
    if(t>0)
    {
        FinalGrid=solver.getFinalGrid0();
        std::vector<int> depths=solver.getLeastAndMostDepth();
        QMessageBox* box=new QMessageBox;
        QString Info;
        Info+="Original Clue Number is:\t"+QString::number(solver.ClueNumber(GridNumbers));
        Info+="\r\nDetected Clue Found in First Search:"+QString::number(solver.ClueNumber(solver.getGrid()));
        Info+="\r\nThe Solution Number is:\t"+QString::number(t);
        Info+="\r\nNeeded Least Guess is:"+QString::number(depths[0]);
        Info+="\r\nNeeded  Most Guess is:"+QString::number(depths[1]);

        box->setText(Info);
        box->setWindowIcon(QIcon(":/resources/others/SudokuGame.jpg"));
        box->show();
    }
    else
    {
        QMessageBox* box=new QMessageBox;
        QString Info;
        Info+="Original Clue Number is:\t"+QString::number(solver.ClueNumber(GridNumbers));
        Info+="\r\nDetected Combined Clue:"+QString::number(solver.ClueNumber(solver.getGrid()));
        Info+="\r\nFailed to find Solution";
        box->setText(Info);
        box->setWindowIcon(QIcon(":/resources/others/SudokuGame.jpg"));
        box->show();
    }
}
