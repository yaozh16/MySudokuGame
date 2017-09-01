#include "MySudokuNumberOperation.h"

SudokuOperationNumberWidget::SudokuOperationNumberWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout* SudokuOperationLayout=new QGridLayout;
    SudokuOperationLayout->setSpacing(0);
    SudokuOperationLayout->setContentsMargins(0,0,0,0);
    for(int i=1;i<10;i++)
    {
        QPushButton* btn=new QPushButton;
        btn->setObjectName("Number"+QString::number(i,10));
        btn->setFixedSize(QSize(60,60));
        QString url="/resources/numbers/"+QString::number(i,10)+".jpg);";

        QString style;
        style+="QPushButton{";
        style+="border-image: url(:";
        style+=url;
        style+="border:4px solid white;";
        style+="border-radius:3px}";
        btn->setStyleSheet(style);
        SudokuOperationLayout->addWidget(btn,1+(i-1)*70,1,70,70);
        connect(btn,SIGNAL(clicked(bool)),parent,SLOT(OnNumberClicked()));
    }
    setLayout(SudokuOperationLayout);
}
