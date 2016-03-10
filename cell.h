#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QPixmap>

class Cell : public QObject
{
    Q_OBJECT

    /*
     * opened?
    */
    bool m_state;

    /*
     * 0 - empty, 9 - bomb
    */
    int m_contents;

public:
    explicit Cell(QObject *parent = 0);

    bool state();
    bool isBomb();

    QPixmap open();

    void setContents(int c);

signals:

public slots:
};

#endif // CELL_H
