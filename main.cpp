#include "mainwindow.h"
#include "minefield.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    MineField mf;
    w.setField(&mf);

    mf.show();

    return a.exec();
}
