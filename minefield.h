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

private:
    QVector< QVector< Cell > > m_field;

    int m_width;
    int m_height;
    int m_bombs;
    int m_cellSize;
    bool m_frozen;

    int m_openedCells;
    int m_markedCells;

    void countNumbers();
    void placeBombs(int amount, int startX, int startY);
    void createField();
    void openCell(int x, int y);
    bool empty(int x, int y);
    bool bomb(int x, int y);

    QPoint getPositionOffset();

public:
    explicit MineField(QWidget *parent = 0);

    void generateField(int startX, int startY);
    void setProperties(int height, int width, int bombs);
    void setCellSize(int s);
    void showBombs();

    void freeze(bool f) { m_frozen = f; }

    int fullWidth() { return m_width * m_cellSize; }
    int fullHeight() { return m_height * m_cellSize; }

    int bombs() { return m_bombs; }
    int width() { return m_width; }
    int height() { return m_height; }

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void cellOpened(int all);
    void gameStarted();
    void gameFailed();
    void cellMarked(int all);

public slots:
};

#endif // MINEFIELD_H
