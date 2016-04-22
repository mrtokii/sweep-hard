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
            painter.drawPixmap(0, 0, 50, 50, QPixmap("://images/ClosedCell.png"));
        break;

        case cellOpened:
            painter.drawPixmap(0, 0, 50, 50, QPixmap("://images/OpenedCell.png"));

            if(contents() != 0) {
                painter.drawPixmap(0, 0, 50, 50, QPixmap("://images/Numbers/" + QString::number(contents()) + ".png"));
            }
        break;

        case cellMarked:
            painter.drawPixmap(0, 0, 50, 50, QPixmap("://images/MarkedCell.png"));
        break;

        case cellBomb:
            painter.drawPixmap(0, 0, 50, 50, QPixmap("://images/BombCell.png"));
        break;
    }

    return pic;
}

void Cell::setContents(int c)
{
    this->m_contents = c;
}

