#include "minefield.h"
#include <QtDebug>
#include <QMessageBox>

void MineField::placeBombs(int amount, int startX, int startY)
{
    qDebug() << "AMOUNT: " << amount;
    qDebug() << "START: " << startX << " " << startY;

    for(int i = 0; i < amount;) {
        int randomH = rand()%h;       
        int randomW = rand()%w;

        if(!m_field[randomH][randomW].isBomb() && !(randomH == startY && randomW == startX)) {
            m_field[randomH][randomW].setContents(9);
            qDebug() << "RAND FOUND: " << randomW << " " << randomH;
            i++;
        }

        update();
    }
}

void MineField::createField()
{
    m_field = QVector< QVector< Cell > >(h);

    for(int i = 0; i < h; i++) {
        m_field[i] = QVector< Cell >(w);
    }

    m_gameStarted = false;
    update();
}

void MineField::openCell(int x, int y)
{
    if(x >= 0 && x < w && y >= 0 && y < h) {
        if(!m_field[y][x].opened() && !m_field[y][x].isBomb()) {
            m_field[y][x].open();

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
    if(x >= 0 && x < w && y >= 0 && y < h) {
        if(m_field[y][x].empty())
            return true;
        else
            return false;
    }

    return false;
}

void MineField::countNumbers()
{
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {

            if(!m_field[i][j].isBomb()) {
                if(i > 0 && j > 0 && m_field[i-1][j-1].isBomb()) // 7
                    m_field[i][j].increment();
                if(i > 0 && m_field[i-1][j].isBomb()) // 8
                    m_field[i][j].increment();
                if(i > 0 && j < w-1 && m_field[i-1][j+1].isBomb()) // 9
                    m_field[i][j].increment();
                if(j > 0 && m_field[i][j-1].isBomb()) // 4
                    m_field[i][j].increment();
                if(j < w-1 && m_field[i][j+1].isBomb()) // 6
                    m_field[i][j].increment();
                if(i < h-1 && j > 0 && m_field[i+1][j-1].isBomb()) // 1
                    m_field[i][j].increment();
                if(i < h-1 && m_field[i+1][j].isBomb()) // 2
                    m_field[i][j].increment();
                if(i < h-1 && j < w-1 && m_field[i+1][j+1].isBomb()) // 3
                    m_field[i][j].increment();

            }

        }
    }
}

MineField::MineField(QWidget *parent) : QWidget(parent)
{
    m_gameStarted = false;
    h = 1;
    w = 1;
    m_bombs = 1;
}

void MineField::generateField(int startX, int startY)
{   
    placeBombs(m_bombs, startX, startY);
    countNumbers();
    update();
}

void MineField::setProperties(int height, int width, int bombs)
{
    if(bombs < width * height) {
        w = width;
        h = height;
        m_bombs = bombs;

        createField();
    }
}

void MineField::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            painter.drawPixmap(j*50, i*50, 50, 50, m_field[i][j].draw());
        }
    }
}

void MineField::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > w*50-1 || event->pos().y() > h*50-1)
        return;


    if (event->button() == Qt::LeftButton) {
        QPoint newCoords;
        newCoords.setX(event->pos().x() / 50);
        newCoords.setY(event->pos().y() / 50);
        qDebug() << "FieldClick: " << newCoords.x() << " " << newCoords.y();

        if(!m_gameStarted) {
            generateField(newCoords.x(), newCoords.y());
            m_gameStarted = true;
        }


        if(m_field[newCoords.y()][newCoords.x()].isBomb()) {
            QMessageBox msgBox;
            msgBox.setText("ITS A TRAP");
            msgBox.exec();
        } else {
            openCell(newCoords.x(), newCoords.y());
        }
    }

    this->update();
}


