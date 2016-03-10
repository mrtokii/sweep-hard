#include "cell.h"

Cell::Cell(QObject *parent) : QObject(parent)
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
    // placeholder
    return QPixmap();
}

void Cell::setContents(int c)
{
    this->m_contents = c;
}

