#ifndef CELL_H
#define CELL_H

#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Cell
{

protected:
    /*
     * 0 - not opened
     * 1 - marked
     * 2 - opened
    */
    int m_state;
    enum { cellNotOpened, cellMarked, cellOpened, cellBomb };

    /*
     * 0 - empty, 9 - bomb
    */
    int m_contents;

public:
    explicit Cell();
    explicit Cell(int size);

    bool opened() { return this->m_state == cellOpened; }
    bool isBomb() { return this->m_contents == 9; }
    bool empty() { return this->m_contents == 0; }
    bool marked() { return this->m_state == cellMarked; }

    int contents() { return this->m_contents; }

    void open() { this->m_state = cellOpened; }
    void increment() { this->m_contents++; }
    void mark(bool state) { this->m_state = state ? cellMarked : cellNotOpened; }
    bool invertMark() { mark(!marked()); return marked(); }
    void showBomb() { this->m_state = cellBomb; }

    QPixmap draw();

    void setContents(int c);

signals:

public slots:
};

#endif // CELL_H
