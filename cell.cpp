#include "cell.h"

Cell::Cell()
{
    this->m_state = cellNotOpened;
    this->m_contents = 0;
}

QPixmap Cell::draw()
{   
    QPixmap pic(50, 50);
    QPainter painter(&pic);

    // Base color
    painter.fillRect(0, 0, 50, 50, Qt::red);

    switch(m_state) {
        case cellNotOpened:
            painter.fillRect(1, 1, 48, 48, Qt::black);
        break;

        case cellOpened:
            if(!this->isBomb()) {
                painter.fillRect(1, 1, 48, 48, Qt::blue);

                painter.setPen(Qt::white);

                QFont font = painter.font() ;
                font.setPointSize(10);
                painter.setFont(font);
                painter.drawText(QPoint(21, 28), QString::number(this->m_contents));
            }
        break;

        case cellMarked:
            painter.fillRect(1, 1, 48, 48, Qt::green);
        break;

        case cellBomb:
            painter.fillRect(1, 1, 48, 48, Qt::white);
        break;
    }

    return pic;
}

void Cell::setContents(int c)
{
    this->m_contents = c;
}

