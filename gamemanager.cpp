#include "gamemanager.h"
#include "newgamedialog.h"
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDebug>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    m_gameField = NULL;
    m_startTime = QTime::currentTime();
    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

GameManager::~GameManager()
{
    delete m_timer;
}

void GameManager::connectField(MineField *f)
{
    m_gameField = f;
    QObject::connect(m_gameField, SIGNAL(cellOpened(int)), this, SLOT(cellOpened(int)));
    QObject::connect(m_gameField, SIGNAL(gameStarted()), this, SLOT(gameStarted()));
    QObject::connect(m_gameField, SIGNAL(gameFailed()), this, SLOT(gameFailed()));
    QObject::connect(m_gameField, SIGNAL(cellMarked(int)), this, SLOT(cellMarked(int)));
    QObject::connect(m_gameField, SIGNAL(gamePrepared()), this, SLOT(gamePrepared()));
}

void GameManager::connectTimer(QLabel *t)
{
    m_timerPanel = t;
}

void GameManager::connectInfoPanel(QLabel *p)
{
    m_infoPanel = p;
}

void GameManager::newGame()
{
    NewGameDialog dialog(this);
    dialog.exec();
}

void GameManager::newGame(int level)
{
    if(m_gameField == NULL)
        return;

    m_gameLevel = level;
    m_gameField->clearMessageText();

    switch(level) {
        case easy:
            m_gameField->setProperties(9, 9, 10);
        break;

        case medium:
            m_gameField->setProperties(30, 18, 25);
        break;

        case hard:
            m_gameField->setProperties(18, 30, 40);
        break;
    }

}

void GameManager::newGame(int w, int h, int bombs)
{
    if(m_gameField == NULL)
        return;

    m_gameField->clearMessageText();
    m_gameLevel = custom;
    m_gameField->setProperties(h, w, bombs);

    cellMarked(0);
}

void GameManager::cellOpened(int all)
{
    int fieldSize = m_gameField->width() * m_gameField->height();

    // Игра закончилась победой
    if(fieldSize - all == m_gameField->bombs()) {
        m_gameField->freeze(true);
        m_timer->stop();
        m_gameTime = gameTime();

        m_infoPanel->setText("U WON");
        m_gameField->setMessageText("Вы ВЫИГРАЛИ!!!");

        /*QMessageBox msgBox;
        msgBox.setText("U WON");
        msgBox.exec();*/
    }

}

void GameManager::cellMarked(int a)
{
        m_infoPanel->setText(QString::number(m_gameField->bombs() - a));
}

void GameManager::gameStarted()
{
    m_startTime.start();
    m_timer->start(300);
    updateTimer();
}

void GameManager::gameFailed()
{
    m_timer->stop();
    m_gameField->showBombs();

    m_infoPanel->setText("U FAILED");
    m_gameField->setMessageText("Вы проиграли :(");

    /*QMessageBox msgBox;
    msgBox.setText("U FAILED");
    msgBox.exec();*/
}

void GameManager::gamePrepared()
{
    m_timer->stop();
}

void GameManager::updateTimer()
{
    m_timerPanel->setText(gameTime().toString("mm:ss"));
}

QTime GameManager::gameTime()
{
    int ms = m_startTime.elapsed();
    int s  = ms / 1000;    ms %= 1000;
    int m  = s  / 60;      s  %= 60;
    int h  = m  / 60;      m  %= 60;
    return QTime(h, m, s, ms);
}
