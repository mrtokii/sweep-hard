#ifndef CELL_H
#define CELL_H

#include <QPixmap>
#include <QPainter>

class Cell
{

    /*
     * opened?
    */
    bool m_state;

    /*
     * 0 - empty, 9 - bomb
    */
    int m_contents;

public:
    explicit Cell();

    bool state();
    bool isBomb();

    QPixmap open();

    void setContents(int c);

signals:

public slots:
};

#endif // CELL_H
