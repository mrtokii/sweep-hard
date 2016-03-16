#include "mainwindow.h"
#include "minefield.h"
#include "gamemanager.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QLabel *timer = new QLabel("timer");
    timer->show();
    QLabel *info = new QLabel("info");
    info->show();

    MineField* mf = new MineField();
    GameManager *gm = new GameManager();
    gm->connectField(mf);
    gm->connectTimer(timer);
    gm->connectInfoPanel(info);

    w.setField(mf);

    gm->newGame(GameManager::easy);

    mf->show();

    return a.exec();
}
