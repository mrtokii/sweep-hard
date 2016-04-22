#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T22:09:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minesweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    minefield.cpp \
    gamemanager.cpp \
    newgamedialog.cpp \
    qstylesheet.cpp

HEADERS  += mainwindow.h \
    cell.h \
    minefield.h \
    gamemanager.h \
    newgamedialog.h \
    qstylesheet.h

FORMS    += mainwindow.ui \
    newgamedialog.ui

RESOURCES += \
    resources.qrc
