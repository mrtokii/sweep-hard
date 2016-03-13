#include "cell.h"

Cell::Cell()
{
    this->m_opened = false;
    this->m_contents = 0;
}

QPixmap Cell::draw()
{   
    QPixmap pic(50, 50);
    QPainter painter(&pic);

    if(m_opened) { // Рисуем открытую клетку
        painter.fillRect(0, 0, 50, 50, Qt::red);

        if(!this->isBomb()) {
            painter.fillRect(1, 1, 48, 48, Qt::blue);

            painter.setPen(Qt::white);

            QFont font = painter.font() ;
            font.setPointSize(10);
            painter.setFont(font);
            painter.drawText(QPoint(5, 20), QString::number(this->m_contents));
        }


    } else { // Рисуем закрытую клетку
        painter.fillRect(0, 0, 50, 50, Qt::red);
        painter.fillRect(1, 1, 48, 48, Qt::black);
    }


    return pic;
}

void Cell::setContents(int c)
{
    this->m_contents = c;
}

