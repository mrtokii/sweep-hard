#ifndef CELL_H
#define CELL_H

#include <QPixmap>
#include <QPainter>

class Cell
{

    /*
     * opened?
    */
    bool m_opened;

    /*
     * 0 - empty, 9 - bomb
    */
    int m_contents;

public:
    explicit Cell();

    bool opened() { return this->m_opened; }
    bool isBomb() { return this->m_contents == 9; }
    int contents() { return this->m_contents; }

    void open() { this->m_opened = true; }
    void increment() { this->m_contents++; }

    QPixmap draw();

    void setContents(int c);

signals:

public slots:
};

#endif // CELL_H
