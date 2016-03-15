#include "gamemanager.h"
#include <QMessageBox>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    m_gameField = NULL;
}

void GameManager::connectField(MineField *f)
{
    m_gameField = f;
    QObject::connect(m_gameField, SIGNAL(cellOpened(int)), this, SLOT(cellOpened(int)));
    QObject::connect(m_gameField, SIGNAL(gameStarted()), this, SLOT(gameStarted()));
    QObject::connect(m_gameField, SIGNAL(gameFailed()), this, SLOT(gameFailed()));
}

void GameManager::newGame(int level)
{
    if(m_gameField == NULL)
        return;

    switch(level) {
        case easy:
            m_gameField->setProperties(9, 9, 10);
        break;

        case medium:
            m_gameField->setProperties(15, 15, 25);
        break;

        case hard:
            m_gameField->setProperties(20, 20, 40);
        break;
    }
}

void GameManager::newGame(int w, int h, int bombs)
{
    if(m_gameField == NULL)
        return;

    m_gameField->setProperties(h, w, bombs);
}

void GameManager::cellOpened(int all)
{
    int fieldSize = m_gameField->width() * m_gameField->height();

    if(fieldSize - all == m_gameField->bombs()) {
        QMessageBox msgBox;
        msgBox.setText("U WON");
        msgBox.exec();
    }
}

void GameManager::gameStarted()
{

}

void GameManager::gameFailed()
{
    QMessageBox msgBox;
    msgBox.setText("U FAILED");
    msgBox.exec();
}

