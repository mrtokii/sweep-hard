#include "cell.h"

Cell::Cell()
{
    this->m_state = false;
    this->m_contents = 0;
}

bool Cell::state()
{
    return this->m_state;
}

bool Cell::isBomb()
{
    return this->m_contents == 9;
}

QPixmap Cell::open()
{   
    QPixmap pic(50, 50);
    QPainter painter(&pic);

    //painter.setBrush(QBrush(Qt::blue, Qt::CrossPattern));

    painter.fillRect(0, 0, 50, 50, Qt::white);
    painter.fillRect(2, 2, 48, 48, Qt::blue);

    painter.setPen(Qt::white);

    QFont font = painter.font() ;
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(QPoint(5, 20), QString::number(this->m_contents));

    return pic;
}

void Cell::setContents(int c)
{
    this->m_contents = c;
}

