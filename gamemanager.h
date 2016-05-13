#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QVector>
#include "record.h"
#include "minefield.h"

class GameManager : public QObject
{
    Q_OBJECT

    MineField *m_gameField;
    QLabel *m_timerPanel;
    QLabel *m_infoPanel;

    QTime m_startTime;
    QTime m_gameTime;
    QTimer* m_timer;

    int m_gameLevel;

    QTime gameTime();

    QVector<Record> m_recordsE;
    QVector<Record> m_recordsM;
    QVector<Record> m_recordsH;

    void readRecords(int diff);
    void writeRecords(int diff);

public:
    enum { easy, medium, hard, custom };

    explicit GameManager(QObject *parent = 0);
    ~GameManager();

    void connectField(MineField *f);
    void connectTimer(QLabel *t);
    void connectInfoPanel(QLabel *p);

    void newGame();
    void newGame(int level);
    void newGame(int w, int h, int bombs);

    void showRecords();

signals:

public slots:
    void cellOpened(int all);
    void cellMarked(int a);
    void gameStarted();
    void gameFailed();
    void gamePrepared();

    void updateTimer();
};

#endif // GAMEMANAGER_H
