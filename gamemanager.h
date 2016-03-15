#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "minefield.h"

class GameManager : public QObject
{
    Q_OBJECT

    MineField *m_gameField;

public:
    enum { easy, medium, hard };

    explicit GameManager(QObject *parent = 0);

    void connectField(MineField *f);
    void connectTimer();
    void connectInfoPanel();

    void newGame(int level);
    void newGame(int w, int h, int bombs);

signals:

public slots:
    void cellOpened(int all);
    void gameStarted();
    void gameFailed();
};

#endif // GAMEMANAGER_H
