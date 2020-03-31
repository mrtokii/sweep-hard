#include "mainwindow.h"
#include "minefield.h"
#include "gamemanager.h"
#include "qstylesheet.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStyleSheet mainStyle("://styles/app.css");


    MainWindow w;
    w.setStyleSheet(mainStyle.style());
    w.show();

    QLabel *timer = new QLabel("timer");
    QLabel *info = new QLabel("info");

    GameManager *gm = new GameManager();
    gm->connectTimer(timer);
    gm->connectInfoPanel(info);

    gm->newGame(GameManager::easy);

    return a.exec();
}
