#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentNumber(0)
{

    ui->setupUi(this);

    this->setFixedSize(620,640);

    QWidget* mainFrameWidget=new QWidget(this);
    mainFrameWidget->setObjectName("mainFrameWidget");
    mainFrameWidget->setGeometry(0,0,640,640);

    {
        QString style;
        style+="background-color: rgb(212, 253, 255);";//"border-image: url(:/resources/numbers/0.jpg);";

        mainFrameWidget->setStyleSheet(style);
    }


    My_Sudoku_Grid_Widget=new SudokuGridWidget(this);
    My_Sudoku_Grid_Widget->setContentsMargins(0,0,0,0);
    My_Sudoku_Grid_Widget->setGeometry(4,80, 556, 556);


    //数字操作面板
    My_Sudoku_Number_Widget=new SudokuOperationNumberWidget(this);
    My_Sudoku_Number_Widget->setGeometry(560,0,80,640);
    My_Sudoku_Number_Widget->setContentsMargins(0,0,0,0);

    //游戏控制面板
    My_Game_Operation_Widget=new GameOperationWidget(this);
    My_Game_Operation_Widget->setGeometry(1,1,540,80);
    My_Game_Operation_Widget->setContentsMargins(10,10,10,10);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete My_Game_Operation_Widget;
    delete My_Sudoku_Grid_Widget;
    delete My_Sudoku_Number_Widget;
}

void MainWindow::OnRestartClicked()
{
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
    qDebug()<<"--OnNumberClicked()\r\n\tCurrentNumber is :"<<currentNumber;
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    QString name=btn->objectName();
    name.remove(0,6);
    currentNumber=name.toInt();
    qDebug()<<"\tCurrentNumber to :"<<currentNumber;
}
int MainWindow::Init()
{
    connect(My_Game_Operation_Widget,SIGNAL(Game_Pause_Clicked(bool)),My_Sudoku_Grid_Widget,SLOT(Grid_Pause(bool)));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Restart_Clicked(int)),My_Sudoku_Grid_Widget,SLOT(Grid_Import(int)));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Back_Operation()),My_Sudoku_Grid_Widget,SLOT(Grid_Back()));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Forward_Operation()),My_Sudoku_Grid_Widget,SLOT(Grid_Forward()));
    return 0;
}
