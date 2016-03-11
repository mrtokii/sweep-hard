#include "minefield.h"
#include <QtDebug>

MineField::MineField(QWidget *parent) : QWidget(parent)
{
    w = 5;
    h = 5;

    m_field = QVector< QVector< Cell > >(h);

    for(int i = 0; i < h; i++) {
        m_field[i] = QVector< Cell >(w);
    }


}

void MineField::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            painter.drawPixmap(j*50, i*50, 50, 50, m_field[i][j].open());
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
        m_field[newCoords.y()][newCoords.x()].setContents(5);
    }

    this->update();
}


