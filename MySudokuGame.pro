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
    #GameBase/MySudokuGenerater.cpp \
    #GameBase/MySudokuSolver.cpp
    GameBase/MySudokuGenerater.cpp \
    GameBase/MySudokuSolver.cpp

HEADERS  += mainwindow.h \
    #GameBase/MySudokuGenerater.h \
    #GameBase/MySudokuSolver.h
    GameBase/MySudokuGenerater.h \
    GameBase/MySudokuSolver.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresource.qrc

