#include "gamemanager.h"
#include "newgamedialog.h"
#include "recordsdialog.h"
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QInputDialog>
#include <QStringList>
#include <QDebug>

static const char* const FILE_NAME = "D:/minesweeperSave";

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    m_gameField = NULL;
    m_startTime = QTime::currentTime();
    m_timer = new QTimer(this);

    readRecords(easy);
    readRecords(medium);
    readRecords(hard);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

GameManager::~GameManager()
{
    delete m_timer;

    writeRecords(easy);
    writeRecords(medium);
    writeRecords(hard);
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
            m_gameField->setProperties(9, 9, 3, 20);
        break;

        case medium:
            m_gameField->setProperties(16, 16, 3, 80);
        break;

        case hard:
            m_gameField->setProperties(16, 30, 3, 199);
        break;
    }

}

void GameManager::newGame(int w, int h, int bombs)
{
    if(m_gameField == NULL)
        return;

    m_gameField->clearMessageText();
    m_gameLevel = custom;
    m_gameField->setProperties(h, w, 9, bombs);

    cellMarked(0);
}

void GameManager::showRecords()
{
    RecordsDialog rd(&m_recordsE, &m_recordsM, &m_recordsH);
    rd.exec();
}

void GameManager::cellOpened(int all)
{
    int fieldSize = m_gameField->width() * m_gameField->height() * m_gameField->depth();

    // Игра закончилась победой
    if(fieldSize - all == m_gameField->bombs()) {
        m_gameField->freeze(true);
        m_timer->stop();
        m_gameTime = gameTime();

        m_infoPanel->setText("YOU WON!");
        m_gameField->setMessageText("YOU WON!");

        // Проверка на режим игры:
        // Если не настраиваемый, то отслеживаем рекорды
        QVector<Record> *records;
        switch(m_gameLevel) {
            case easy:
                records = &m_recordsE;
            break;

            case medium:
                records = &m_recordsM;
            break;

            case hard:
                records = &m_recordsH;
            break;

            default:
                return;
        }

        // Запись рекорда в список рекордов
        if(records->empty() || m_gameTime < records->at(0).time()) {
            bool ok;

            // Fix later

            /*
            QWidget *w;

            QString wName = QInputDialog::getText(w, tr("Enter your name:"),
                                                 tr("Winner:"), QLineEdit::Normal,
                                                 "Player", &ok);
            if (ok && !wName.isEmpty()) {
                records->push_front(Record(m_gameTime, wName));
                m_infoPanel->setText("New record!");
            }
            */
        }


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

    m_infoPanel->setText("Start a game");
    m_gameField->setMessageText("YOU LOSE :(");
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

void GameManager::readRecords(int diff)
{
    QVector<Record> *container;
    QString fileSuffix;

    switch(diff) {
        case easy:
            container = &m_recordsE;
            fileSuffix = "Easy";
        break;

        case medium:
            container = &m_recordsM;
            fileSuffix = "Medium";
        break;

        case hard:
            container = &m_recordsH;
            fileSuffix = "Hard";
        break;
    }

    QFile file(FILE_NAME + fileSuffix + ".txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString string = in.readLine();
            QStringList sl = string.split("||");

            int ms = sl.at(0).toInt();
            int s  = ms / 1000;    ms %= 1000;
            int m  = s  / 60;      s  %= 60;
            int h  = m  / 60;      m  %= 60;
            QTime time(h, m, s, ms);

            Record r(time, sl.at(1));
            container->append(r);
      }
       file.close();
    }
}

void GameManager::writeRecords(int diff)
{
    QVector<Record> *container;
    QString fileSuffix;

    switch(diff) {
        case easy:
            container = &m_recordsE;
            fileSuffix = "Easy";
        break;

        case medium:
            container = &m_recordsM;
            fileSuffix = "Medium";
        break;

        case hard:
            container = &m_recordsH;
            fileSuffix = "Hard";
        break;
    }

    QFile file(FILE_NAME + fileSuffix + ".txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             QTextStream writeStream(&file);
             writeStream.setCodec("UTF-8");
             for (int i=0, s = container->length(); i < s ; i++)
             {
                QString str = container->at(i).compact();

                if(i != s-1)
                    str += "\n";

                writeStream << str;
             };
         };
    file.close();
}

