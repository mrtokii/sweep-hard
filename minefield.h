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

    int w;
    int h;


    void countNumbers();
    void placeBombs(int amount);

public:
    explicit MineField(QWidget *parent = 0);

    void generateField(int height, int width, int bombs);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // MINEFIELD_H
