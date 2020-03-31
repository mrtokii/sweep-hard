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
    QVector<QVector<QVector<Cell>>> m_field;

    int m_width;
    int m_height;
    int m_depth;

    int m_currentDepth;

    int m_bombs;
    int m_cellSize;
    bool m_frozen;

    int m_highlightX;
    int m_highlightY;

    QString m_messageText;

    int m_openedCells;
    int m_markedCells;

    void countNumbers();
    void placeBombs(int amount, int startX, int startY, int startZ);
    void createField();
    void openCell(int x, int y, int z);
    bool empty(int x, int y, int z);
    bool bomb(int x, int y,int z);
    bool forceOpen(int x, int y, int z);

    QPoint getPositionOffset();

public:
    explicit MineField(QWidget *parent = 0);

    bool m_highlight;

    void generateField(int startX, int startY, int startZ);
    void setProperties(int height, int width, int depth, int bombs);
    void setCellSize(int s);
    void showBombs();

    void freeze(bool f) { m_frozen = f; }

    int fullWidth() { return m_width * m_cellSize; }
    int fullHeight() { return m_height * m_cellSize; }

    int bombs() { return m_bombs; }
    int width() { return m_width; }
    int height() { return m_height; }
    int depth() { return m_depth; }

    int currentDepth() { return m_currentDepth; }

    void setCurrentDepth(int newValue) { m_currentDepth = newValue; }

    void setMessageText(QString message) { m_messageText = message; }
    void clearMessageText() { m_messageText = ""; }

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void cellOpened(int all);
    void gameStarted();
    void gameFailed();
    void cellMarked(int all);
    void gamePrepared();

public slots:

};

#endif // MINEFIELD_H
