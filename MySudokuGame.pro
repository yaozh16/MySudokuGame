#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T15:08:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySudokuGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GameBase/MySudokuGenerater.cpp \
    GameBase/MySudokuSolver.cpp \
    MyWidgets/MyGameOperation.cpp \
    MyWidgets/MySudokuGrid.cpp \
    MyWidgets/MySudokuNumberOperation.cpp \
    MyWidgets/MyGridButtonWithBoard.cpp

HEADERS  += mainwindow.h \
    GameBase/MySudokuGenerater.h \
    GameBase/MySudokuSolver.h \
    MyWidgets/MyGameOperation.h \
    MyWidgets/MySudokuGrid.h \
    MyWidgets/MySudokuNumberOperation.h \
    MyWidgets/MyGridButtonWithBoard.h

FORMS    += mainwindow.ui

RESOURCES += \
    myqtresource.qrc

