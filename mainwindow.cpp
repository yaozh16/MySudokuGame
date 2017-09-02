#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowIcon(QIcon("/resources/others/SudokuGame.jpg"));

    this->setWindowTitle("My Sudoku Game");
    this->setFixedSize(620,640);

    My_Sudoku_Grid_Widget=new SudokuGridWidget(this);
    My_Sudoku_Grid_Widget->setContentsMargins(0,0,0,0);
    My_Sudoku_Grid_Widget->setGeometry(4,80, 556, 556);


    //数字操作面板
    My_Sudoku_Number_Widget=new SudokuOperationNumberWidget(this);
    My_Sudoku_Number_Widget->setGeometry(550,80,80,560);
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
int MainWindow::Init()
{
    connect(My_Game_Operation_Widget,SIGNAL(Game_Pause_Clicked(bool)),My_Sudoku_Grid_Widget,SLOT(Grid_Pause(bool)));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Restart_Clicked(int)),My_Sudoku_Grid_Widget,SLOT(Grid_Import(int)));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Back_Operation()),My_Sudoku_Grid_Widget,SLOT(Grid_Back()));
    connect(My_Game_Operation_Widget,SIGNAL(Game_Forward_Operation()),My_Sudoku_Grid_Widget,SLOT(Grid_Forward()));
    connect(My_Sudoku_Grid_Widget,SIGNAL(Grid_Clue_Broadcast(int)),My_Game_Operation_Widget,SLOT(Game_Clue_Show(int)));
    connect(My_Sudoku_Grid_Widget,SIGNAL(Grid_Finished()),My_Game_Operation_Widget,SLOT(Game_Finish()));
    connect(My_Sudoku_Number_Widget,SIGNAL(Number_SelectBroadCast(int)),My_Sudoku_Grid_Widget,SLOT(Grid_Select(int)));
    connect(My_Sudoku_Grid_Widget,SIGNAL(Grid_Step_State(int)),My_Game_Operation_Widget,SLOT(Game_Step_Update(int)));
    connect(My_Sudoku_Number_Widget,SIGNAL(Number_AutoStep()),My_Sudoku_Grid_Widget,SLOT(Grid_AutoStep()));
    return 0;
}
