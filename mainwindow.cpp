#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentNumber(0)
{

    ui->setupUi(this);

    this->setFixedSize(620,640);

    for(int i=0;i<81;i++)
    {
        QVector<int> tem;
        MarkedNumbers.push_back(tem);
    }
    QWidget* mainFrameWidget=new QWidget(this);
    mainFrameWidget->setObjectName("mainFrameWidget");
    mainFrameWidget->setGeometry(0,0,640,640);

    {
        QString style;
        style+="background-color: rgb(212, 253, 255);";//"border-image: url(:/resources/numbers/0.jpg);";

        mainFrameWidget->setStyleSheet(style);
    }


    SudokuGridLayoutWidget=new QWidget(mainFrameWidget);
    SudokuGridLayoutWidget->setContentsMargins(0,0,0,0);
    SudokuGridLayoutWidget->setGeometry(4,80, 556, 556);
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
            QPushButton* button=new QPushButton;
            button->setFixedSize(60,60);
            button->setObjectName(QString::number(i*10+j,10));
            QString style;
            style+="QPushButton{";
            style+="border-image: url(:/resources/numbers/0.jpg);";
            style+="border:1px solid white;";
            style+="border-radius:5px}";
            button->setStyleSheet(style);
            QGridLayout* markerLayout=new QGridLayout(button);
            SudokuGridLayout->addWidget(button,(i+2)/3*4+(i-1)*60,(j+2)/3*4+(j-1)*60,60,60);
            connect(button,SIGNAL(clicked(bool)),this,SLOT(OnGridClicked()));
        }

    SudokuGridLayoutWidget->setLayout(SudokuGridLayout);

    //数字操作面板
    SudokuOperationLayoutWidget=new QWidget(mainFrameWidget);
    SudokuOperationLayoutWidget->setGeometry(560,0,80,640);
    SudokuOperationLayoutWidget->setContentsMargins(0,0,0,0);
    QGridLayout* SudokuOperationLayout=new QGridLayout;
    SudokuOperationLayout->setSpacing(0);
    SudokuOperationLayout->setContentsMargins(0,0,0,0);
    for(int i=1;i<10;i++)
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Number"+QString::number(i,10));
        btn->setFixedSize(QSize(60,60));

        QString style;
        style+="QPushButton{";
        QString url="/resources/numbers/"+QString::number(i,10)+".jpg);";
        style+="border-image: url(:";
        style+=url;
        style+="border:3px solid white;";
        style+="border-radius:5px}";
        btn->setStyleSheet(style);
        SudokuOperationLayout->addWidget(btn,1+(i-1)*70,1,70,70);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(OnNumberClicked()));
    }
    SudokuOperationLayoutWidget->setLayout(SudokuOperationLayout);
    //游戏控制面板
    GameOperationLayoutWidget=new QWidget(mainFrameWidget);
    GameOperationLayoutWidget->setGeometry(1,1,540,80);
    GameOperationLayoutWidget->setContentsMargins(10,10,10,10);
    QGridLayout* GameOperationLayout=new QGridLayout;
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Restart");
        btn->setFixedSize(75,60);
        btn->setText("重玩");
        QString style;
        style+="QPushButton{";
        style+="border:5px solid black;";
        style+="border-radius:5px}";
        btn->setStyleSheet(style);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(Init()));
        GameOperationLayout->addWidget(btn,1,1,100,75);
    }
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Pause");
        btn->setFixedSize(75,60);
        btn->setText("暂停");
        QString style;
        style+="QPushButton{";
        style+="border:5px solid black;";
        style+="border-radius:5px}";
        btn->setStyleSheet(style);
        GameOperationLayout->addWidget(btn,1,76,100,75);
    }
    {
        QLCDNumber* Number=new QLCDNumber(GameOperationLayoutWidget);
        Number->setObjectName("LCDTimer");
        Number->setSegmentStyle(QLCDNumber::Filled);
        Number->display("00.00");
        GameOperationLayout->addWidget(Number,1,151,100,150);
    }
    GameOperationLayoutWidget->setLayout(GameOperationLayout);
    Import();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnGridClicked()
{
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    QString name=btn->objectName();
    int x=name.toInt()%10;
    int y=name.toInt()/10;
    if(MarkedNumbers[x+y*9-10].size()>0) ;
    if(currentNumber>0&&currentNumber<10)
        SetGrid(x,y,currentNumber);
}
void MainWindow::OnRestartClicked()
{
    ;
}
void MainWindow::OnPauseClicked()
{
    static bool pauseflag=true;
    if(pauseflag)
    {

    }
    else
    {

    }
}
void MainWindow::OnNumberClicked()
{
    ;
}
int MainWindow::Import(int clue)
{
    generater.Generate();
    solver.importGrid(generater.getGrid());
    std::vector<int> tem=solver.setClue(clue);
    if(tem.size()!=81)
        return 1;
    Grid.clear();
    for(int i=0;i<81;i++)
    {
        Grid.push_back(tem[i]);
        SetGrid(i%9+1,i/9+1,Grid[i],"border:5px;border-color: rgb(170, 85, 255);");
    }
    return 0;
}
void MainWindow::SetGrid(int x, int y, int v, QString style)
{
    QPushButton *button=findChild<QPushButton*>(QString::number(x+y*10));
    QString Btnstyle;
    Btnstyle+="QPushButton{";
    Btnstyle+=style;
    Btnstyle+="border-image: url(:/resources/numbers/"+QString::number(v)+".jpg);";
    Btnstyle+="border-radius:5px}";
    button->setStyleSheet(Btnstyle);
    return ;
}
int MainWindow::Init()
{
    Import();
    return 0;
}
