#include "mainwindow.h"
#include "minefield.h"
#include "gamemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    MineField* mf = new MineField();
    GameManager *gm = new GameManager();
    gm->connectField(mf);

    w.setField(mf);

    gm->newGame(GameManager::easy);

    mf->show();

    return a.exec();
}
