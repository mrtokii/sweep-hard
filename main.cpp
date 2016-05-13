#include "mainwindow.h"
#include "minefield.h"
#include "gamemanager.h"
#include "qstylesheet.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QStyleSheet mainStyle("://styles/app.css");
    //a.setStyleSheet(mainStyle.style());

    MainWindow w;
    w.show();

    QLabel *timer = new QLabel("timer");
    QLabel *info = new QLabel("info");

    MineField* mf = new MineField();
    GameManager *gm = new GameManager();
    gm->connectField(mf);
    gm->connectTimer(timer);
    gm->connectInfoPanel(info);

    w.setField(mf);

    gm->newGame(GameManager::easy);

    return a.exec();
}
