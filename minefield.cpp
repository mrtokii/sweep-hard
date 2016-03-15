#include "minefield.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTime>

void MineField::placeBombs(int amount, int startX, int startY)
{
    qDebug() << "AMOUNT: " << amount;
    qDebug() << "START: " << startX << " " << startY;

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    for(int i = 0; i < amount;) {


        int randomY = qrand() % m_height;
        int randomX = qrand() % m_width;


        // Для открытия только нулевых клеток
        bool bombAround = randomX >= startX-1 && randomX <= startX+1
                && randomY >= startY-1 && randomY <= startY+1;

        if(!bombAround && !(randomY == startY && randomX == startX))
        {
            m_field[randomY][randomX].setContents(9);
            i++;
        }

    }
}

void MineField::createField()
{
    m_field = QVector< QVector< Cell > >(m_height);

    for(int i = 0; i < m_height; i++) {
        m_field[i] = QVector< Cell >(m_width);
    }

    m_openedCells = 0;
    update();
}

void MineField::openCell(int x, int y)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height) {
        Cell &current = m_field[y][x];

        if(!current.opened() && !current.isBomb()) {

            current.open();
            emit cellOpened(++m_openedCells);

            if(empty(x, y)) { // Если ячейка пуская, открываем все соседние клетки
                openCell(x - 1, y - 1);
                openCell(x, y - 1);
                openCell(x + 1, y - 1);
                openCell(x - 1, y);
                openCell(x + 1, y);
                openCell(x - 1, y + 1);
                openCell(x, y + 1);
                openCell(x + 1, y + 1);
            } else { // Если не пустая, открываем пустые рядом
                if(empty(x - 1, y - 1)) // 7
                    openCell(x - 1, y - 1);

                if(empty(x, y - 1)) // 8
                    openCell(x, y - 1);

                if(empty(x + 1, y - 1)) // 9
                    openCell(x + 1, y - 1);

                if(empty(x - 1, y)) // 4
                    openCell(x - 1, y);

                if(empty(x + 1, y)) // 6
                    openCell(x + 1, y);

                if(empty(x - 1, y + 1)) // 1
                    openCell(x - 1, y + 1);

                if(empty(x, y + 1)) // 2
                    openCell(x, y + 1);

                if(empty(x + 1, y + 1)) // 3
                    openCell(x + 1, y + 1);
            }
        }
    }
}

bool MineField::empty(int x, int y)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height) {
        if(m_field[y][x].empty())
            return true;
        else
            return false;
    }

    return false;
}

bool MineField::bomb(int x, int y)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height) {
        if(m_field[y][x].isBomb())
            return true;
        else
            return false;
    }

    return false;
}

void MineField::countNumbers()
{
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {

            if(!m_field[i][j].isBomb()) {
                if(i > 0 && j > 0 && m_field[i-1][j-1].isBomb()) // 7
                    m_field[i][j].increment();

                if(i > 0 && m_field[i-1][j].isBomb()) // 8
                    m_field[i][j].increment();

                if(i > 0 && j < m_width-1 && m_field[i-1][j+1].isBomb()) // 9
                    m_field[i][j].increment();

                if(j > 0 && m_field[i][j-1].isBomb()) // 4
                    m_field[i][j].increment();

                if(j < m_width-1 && m_field[i][j+1].isBomb()) // 6
                    m_field[i][j].increment();

                if(i < m_height-1 && j > 0 && m_field[i+1][j-1].isBomb()) // 1
                    m_field[i][j].increment();

                if(i < m_height-1 && m_field[i+1][j].isBomb()) // 2
                    m_field[i][j].increment();

                if(i < m_height-1 && j < m_width-1 && m_field[i+1][j+1].isBomb()) // 3
                    m_field[i][j].increment();

            }

        }
    }
}

MineField::MineField(QWidget *parent) : QWidget(parent)
{
    m_openedCells = 0;
    m_height = 1;
    m_width = 1;
    m_bombs = 1;

    setCellSize(50);
    setProperties(9, 9, 10);
}

void MineField::generateField(int startX, int startY)
{   
    placeBombs(m_bombs, startX, startY);
    countNumbers();
}

void MineField::setProperties(int height, int width, int bombs)
{
    if(bombs < width * height - 8) {
        m_width = width;
        m_height = height;
        m_bombs = bombs;

        createField();
    }
}

void MineField::setCellSize(int s)
{
    m_cellSize = s;
}

void MineField::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            painter.drawPixmap(j * m_cellSize, i * m_cellSize, m_cellSize, m_cellSize, m_field[i][j].draw());
        }
    }
}

void MineField::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > m_width*m_cellSize-1 || event->pos().y() > m_height*m_cellSize-1)
        return;

    QPoint newCoords;
    newCoords.setX(event->pos().x() / m_cellSize);
    newCoords.setY(event->pos().y() / m_cellSize);
    qDebug() << "FieldClick: " << newCoords.x() << " " << newCoords.y();

    if (event->button() == Qt::LeftButton && !m_field[newCoords.y()][newCoords.x()].marked()) {

        if(!m_openedCells) { // Начало игры
            generateField(newCoords.x(), newCoords.y());
            emit gameStarted();
        }


        if(m_field[newCoords.y()][newCoords.x()].isBomb()) {
            emit gameFailed();
        } else {
            openCell(newCoords.x(), newCoords.y());
        }
    } else if(event->button() == Qt::RightButton) {
        if(!m_field[newCoords.y()][newCoords.x()].opened()) {
            m_field[newCoords.y()][newCoords.x()].mark(!m_field[newCoords.y()][newCoords.x()].marked());
        }
    }

    this->update();
}


