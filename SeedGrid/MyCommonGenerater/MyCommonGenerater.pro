TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    MySudokuSolver.cpp \
    MySudokuCommonGenerater.cpp \
    MyDifficultyEvaluater.cpp

HEADERS += \
    MySudokuSolver.h \
    MySudokuCommonGenerater.h \
    MyDifficultyEvaluater.h
