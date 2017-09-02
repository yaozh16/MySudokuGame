#include "MySudokuNumberOperation.h"

SudokuOperationNumberWidget::SudokuOperationNumberWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout* SudokuOperationLayout=new QGridLayout;
    SudokuOperationLayout->setSpacing(0);
    SudokuOperationLayout->setContentsMargins(0,0,0,0);
    //Auto键
    {
        PushButton_AutoStep=new QPushButton;
        PushButton_AutoStep->setObjectName("PushButton_AutoStep");
        PushButton_AutoStep->setFixedSize(QSize(50,50));
        QString style;
        style+="QPushButton{border-image: url(:/resources/operation/Auto.png);}";
        PushButton_AutoStep->setStyleSheet(style);
        SudokuOperationLayout->addWidget(PushButton_AutoStep,1,1,1,1);
        connect(PushButton_AutoStep,&QPushButton::clicked,this,[this](){emit Number_AutoStep();emit Number_SelectBroadCast(0);});
    }
    for(int i=1;i<10;i++)
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Number"+QString::number(i,10));
        btn->setFixedSize(QSize(50,50));

        QString style;
        style+="QPushButton{border-image: url(:/resources/numbers/"+QString::number(i)+".jpg);";
        style+="border:10px solid white;";
        style+="border-radius: 10px;";
        style+="}";
        btn->setStyleSheet(style);
        SudokuOperationLayout->addWidget(btn,i+1,1,1,1);
        connect(btn,&QPushButton::clicked,this,[=](){emit Number_SelectBroadCast(i);});
    }
    setLayout(SudokuOperationLayout);
}
