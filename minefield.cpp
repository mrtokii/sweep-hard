#include "minefield.h"
#include <QtDebug>

void MineField::placeBombs(int amount)
{
    for(int i = 0; i < amount;) {
        int randomH = rand()%h;
        int randomW = rand()%w;

        if(!m_field[randomH][randomW].isBomb()) {
            m_field[randomH][randomW].setContents(9);
            i++;
        }
    }
}

void MineField::countNumbers()
{
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {

            if(!m_field[i][j].isBomb()) {
                if(i > 0 && j > 0 && m_field[i-1][j-1].isBomb()) // 7
                    m_field[i][j].increment();
                if(i > 0 && m_field[i-1][j].isBomb()) // 8
                    m_field[i][j].increment();
                if(i > 0 && j < w-1 && m_field[i-1][j+1].isBomb()) // 9
                    m_field[i][j].increment();
                if(j > 0 && m_field[i][j-1].isBomb()) // 4
                    m_field[i][j].increment();
                if(j < w-1 && m_field[i][j+1].isBomb()) // 6
                    m_field[i][j].increment();
                if(i < h-1 && j > 0 && m_field[i+1][j-1].isBomb()) // 1
                    m_field[i][j].increment();
                if(i < h-1 && m_field[i+1][j].isBomb()) // 2
                    m_field[i][j].increment();
                if(i < h-1 && j < w-1 && m_field[i+1][j+1].isBomb()) // 9
                    m_field[i][j].increment();

            }

        }
    }
}

MineField::MineField(QWidget *parent) : QWidget(parent)
{
    generateField(9, 9, 10);
}

void MineField::generateField(int height, int width, int bombs)
{
    w = width;
    h = height;

    m_field = QVector< QVector< Cell > >(h);

    for(int i = 0; i < h; i++) {
        m_field[i] = QVector< Cell >(w);
    }

    placeBombs(bombs);
    countNumbers();
    update();
}

void MineField::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            painter.drawPixmap(j*50, i*50, 50, 50, m_field[i][j].draw());
        }
    }
}

void MineField::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > w*50 || event->pos().y() > h*50)
        return;

    if (event->button() == Qt::LeftButton) {
        QPoint newCoords;
        newCoords.setX(event->pos().x() / 50);
        newCoords.setY(event->pos().y() / 50);
        qDebug() << "FieldClick: " << newCoords.x() << " " << newCoords.y();
        m_field[newCoords.y()][newCoords.x()].open();
    }

    this->update();
}


