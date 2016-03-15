#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

#include "cell.h"

class MineField : public QWidget
{
    Q_OBJECT

    QVector< QVector< Cell > > m_field;

    int m_width;
    int m_height;
    int m_bombs;

    //bool m_gameStarted;
    int m_openedCells;

    void countNumbers();
    void placeBombs(int amount, int startX, int startY);
    void createField();
    void openCell(int x, int y);
    bool empty(int x, int y);
    bool bomb(int x, int y);

public:
    explicit MineField(QWidget *parent = 0);

    void generateField(int startX, int startY);
    void setProperties(int height, int width, int bombs);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void cellOpened(int all);

public slots:
};

#endif // MINEFIELD_H
