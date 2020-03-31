#include "minefield.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTime>

void MineField::placeBombs(int amount, int startX, int startY, int startZ)
{
    // Разбуриваем генератор случайных чисел
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    for(int i = 0; i < amount;) {
        // Генерируем случайные координаты
        int randomY = qrand() % m_height;
        int randomX = qrand() % m_width;
        int randomZ = qrand() % m_depth;

        // Проверка на то, чтобы рядом со
        // стартовой позицией не было бомб
        bool bombAround =   randomX >= startX-1 && randomX <= startX+1
                         && randomY >= startY-1 && randomY <= startY+1
                         && randomZ >= startZ-1 && randomZ <= startZ+1;

        if(!bombAround && !m_field[randomZ][randomY][randomX].isBomb())
        {
            // Размещаем бомбу
            m_field[randomZ][randomY][randomX].setContents(27);
            i++;
        }

    }
}

void MineField::createField()
{
    m_field = QVector<QVector<QVector<Cell>>>(m_depth);

    for(int i = 0; i < m_depth; i++) {

        m_field[i] = QVector<QVector<Cell>>(m_height);

        for(int j = 0; j < m_height; j++) {
            m_field[i][j] = QVector<Cell>(m_width);
        }
    }

    m_openedCells = 0;
    m_markedCells = 0;
    emit gamePrepared();

    freeze(false);
    emit cellMarked(0);
    update();
}

void MineField::openCell(int x, int y, int z)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height && z >= 0 && z < m_depth) {

        Cell &current = m_field[z][y][x];

        if(!current.opened() && !current.isBomb()) {

            if(current.marked())
                emit cellMarked(--m_markedCells);

            current.open();
            emit cellOpened(++m_openedCells);

            // Если клетка пустая, открываем все соседние клетки
            if(empty(x, y, z)) {

                for(int i = -1; i <= 1; ++i) {
                    openCell(x - 1, y - 1, z + i);
                    openCell(x, y - 1, z + i);
                    openCell(x + 1, y - 1, z + i);
                    openCell(x - 1, y, z + i);
                    openCell(x + 1, y, z + i);
                    openCell(x - 1, y + 1, z + i);
                    openCell(x, y + 1, z + i);
                    openCell(x + 1, y + 1, z + i);
                }

                openCell(x, y, z - 1);
                openCell(x, y, z + 1);

            // Если не пустая, открываем пустые рядом
            } else {

                for(int i = -1; i <= 1; ++i) {

                    if(empty(x - 1, y - 1, z + i))
                        openCell(x - 1, y - 1, z + i);

                    if(empty(x, y - 1, z + i))
                        openCell(x, y - 1, z + i);

                    if(empty(x + 1, y - 1, z + i))
                        openCell(x + 1, y - 1, z + i);

                    if(empty(x - 1, y, z + i))
                        openCell(x - 1, y, z + i);

                    if(empty(x + 1, y, z + i))
                        openCell(x + 1, y, z + i);

                    if(empty(x - 1, y + 1, z + i))
                        openCell(x - 1, y + 1, z + i);

                    if(empty(x, y + 1, z + i))
                        openCell(x, y + 1, z + i);

                    if(empty(x + 1, y + 1, z + i))
                        openCell(x + 1, y + 1, z + i);
                }

                if(empty(x, y, z - 1))
                    openCell(x, y, z - 1);

                if(empty(x, y, z + 1))
                    openCell(x, y, z + 1);
            }
        }
    }
}

bool MineField::empty(int x, int y, int z)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height && z >= 0 && z < m_depth) {
        if(m_field[z][y][x].empty())
            return true;
        else
            return false;
    }

    return false;
}

bool MineField::bomb(int x, int y, int z)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height && z >= 0 && z < m_depth) {
        if(m_field[z][y][x].isBomb())
            return true;
        else
            return false;
    }

    return false;
}

bool MineField::forceOpen(int x, int y, int z)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height && z >= 0 && z < m_depth) {
        if(m_field[z][y][x].marked() || m_field[z][y][x].opened())
            return false;

        openCell(x, y, z);
        if(m_field[z][y][x].isBomb())
            return true;
    }

    return false;
}

// Сдвиг координат поля относительно нуля координат виджета
QPoint MineField::getPositionOffset()
{
    return QPoint(
                (size().width() - fullWidth()) / 2,
                (size().height() - fullHeight()) / 2
            );

}

// Подсчет количества мин рядом с каждой клеткой
void MineField::countNumbers()
{
    for(int k = 0; k < m_depth; k++) {
        for(int i = 0; i < m_height; i++) {
            for(int j = 0; j < m_width; j++) {

                if(!m_field[k][i][j].isBomb()) {

                    // Top

                    if(k > 0 && i > 0 && j > 0 && m_field[k-1][i-1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && i > 0 && m_field[k-1][i-1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && i > 0 && j < m_width-1 && m_field[k-1][i-1][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && j > 0 && m_field[k-1][i][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && j < m_width-1 && m_field[k-1][i][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && i < m_height-1 && j > 0 && m_field[k-1][i+1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && i < m_height-1 && m_field[k-1][i+1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(k > 0 && i < m_height-1 && j < m_width-1 && m_field[k-1][i+1][j+1].isBomb())
                        m_field[k][i][j].increment();

                    // Center

                    if(i > 0 && j > 0 && m_field[k][i-1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(i > 0 && m_field[k][i-1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(i > 0 && j < m_width-1 && m_field[k][i-1][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(j > 0 && m_field[k][i][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(j < m_width-1 && m_field[k][i][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(i < m_height-1 && j > 0 && m_field[k][i+1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(i < m_height-1 && m_field[k][i+1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(i < m_height-1 && j < m_width-1 && m_field[k][i+1][j+1].isBomb())
                        m_field[k][i][j].increment();

                    // Bottom

                    if(k < m_depth-1 && i > 0 && j > 0 && m_field[k+1][i-1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && i > 0 && m_field[k+1][i-1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && i > 0 && j < m_width-1 && m_field[k+1][i-1][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && j > 0 && m_field[k+1][i][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && j < m_width-1 && m_field[k+1][i][j+1].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && i < m_height-1 && j > 0 && m_field[k+1][i+1][j-1].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && i < m_height-1 && m_field[k+1][i+1][j].isBomb())
                        m_field[k][i][j].increment();

                    if(k < m_depth-1 && i < m_height-1 && j < m_width-1 && m_field[k+1][i+1][j+1].isBomb())
                        m_field[k][i][j].increment();
                }
            }
        }
    }
}

MineField::MineField(QWidget *parent) : QWidget(parent)
{
    m_height = 1;
    m_width = 1;
    m_depth = 1;
    m_bombs = 1;

    m_currentDepth = 0;

    m_highlight = false;

    m_highlightX = -1;
    m_highlightY = -1;

    setCellSize(50);
    setProperties(9, 9, 9, 10);
    clearMessageText();

    setMouseTracking(true);
}

void MineField::generateField(int startX, int startY, int startZ)
{   
    placeBombs(m_bombs, startX, startY, startZ);
    countNumbers();
}

void MineField::setProperties(int height, int width, int depth, int bombs)
{
    if(bombs < width * height * depth - 8) {
        m_width = width;
        m_height = height;
        m_depth = depth;
        m_bombs = bombs;

        createField();
    }
}

void MineField::setCellSize(int s)
{
    m_cellSize = s;
}

void MineField::showBombs()
{
    Cell *current;

    for(int k = 0; k < m_depth; k++) {
        for(int i = 0; i < m_height; i++) {
            for(int j = 0; j < m_width; j++) {
                current = &m_field[k][i][j];
                if(current->isBomb())
                    current->showBomb();
            }
        }
    }
}

void MineField::paintEvent(QPaintEvent *e) {

    // Определяем размер клеток исходя из размера виджета
    int minSide = qMin(size().width(), size().height());
    float iRatio = m_width*1.0 / m_height*1.0;
    float oRatio = size().width()*1.0 / size().height()*1.0;
    int side;

    if(oRatio > iRatio)
        setCellSize( size().height() / m_height );
    else
        setCellSize( size().width() / m_width );

    QPainter painter(this);
    painter.fillRect(QRect(0, 0, size().width(), size().height()), QColor(43, 43, 43));

    painter.translate(getPositionOffset());



    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            painter.drawPixmap(j * m_cellSize, i * m_cellSize, m_cellSize, m_cellSize, m_field[m_currentDepth][i][j].draw());
        }
    }

    if(m_highlightX != -1 && m_highlightY != -1) {
        painter.fillRect(QRect(m_highlightX * m_cellSize, m_highlightY * m_cellSize, m_cellSize, m_cellSize), QColor(43, 43, 43, 50));
    }

    // Текстовое сообщение
    if(m_messageText != "") {
        QFont font("arial", 32);
        QFontMetrics fm(font);
        int pixelsWide = fm.width(m_messageText);
        int pixelsHigh = fm.height();
        QRect r = fm.boundingRect(m_messageText);
        r += QMargins(15, 15, 15, 15);

        painter.translate( (fullWidth() - pixelsWide) / 2, (fullHeight() + pixelsHigh) / 2 );
        painter.setFont(font);
        painter.setPen(Qt::white);

        painter.fillRect(r, QColor(43, 43, 43));
        painter.drawText(0, 0, m_messageText);
    }

}

void MineField::mousePressEvent(QMouseEvent *event)
{
    // Проверка на границы поля и на заморозку
    if(        event->pos().x() > fullWidth() + getPositionOffset().x() - 1
            || event->pos().x() < getPositionOffset().x()
            || event->pos().y() > fullHeight() + getPositionOffset().y() - 1
            || event->pos().y() < getPositionOffset().y()
            || m_frozen)
        return;

    // Переход к координатам клетки от абсолютных
    QPoint newCoords;
    newCoords.setX( (event->pos() - getPositionOffset()).x() / m_cellSize);
    newCoords.setY( (event->pos() - getPositionOffset()).y() / m_cellSize);

    Cell &selected = m_field[m_currentDepth][newCoords.y()][newCoords.x()];

    // При нажатии ЛКМ
    if (event->button() == Qt::LeftButton && !selected.marked()) {

        // Начало игры, если ни одной ячейки еще не открыто
        if(!m_openedCells) {
            generateField(newCoords.x(), newCoords.y(), m_currentDepth);
            emit gameStarted();
        }

        if(selected.opened()) {
            bool fail =

                    // Top

                    forceOpen(newCoords.x() - 1, newCoords.y() - 1, m_currentDepth - 1) ||
                    forceOpen(newCoords.x(), newCoords.y() - 1, m_currentDepth - 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() - 1, m_currentDepth - 1) ||
                    forceOpen(newCoords.x() - 1, newCoords.y(), m_currentDepth - 1) ||
                    forceOpen(newCoords.x(), newCoords.y(), m_currentDepth - 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y(), m_currentDepth - 1) ||
                    forceOpen(newCoords.x() - 1, newCoords.y() + 1, m_currentDepth - 1) ||
                    forceOpen(newCoords.x(), newCoords.y() + 1, m_currentDepth - 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() + 1, m_currentDepth - 1) ||

                    // Center

                    forceOpen(newCoords.x() - 1, newCoords.y() - 1, m_currentDepth) ||
                    forceOpen(newCoords.x(), newCoords.y() - 1, m_currentDepth) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() - 1, m_currentDepth) ||
                    forceOpen(newCoords.x() - 1, newCoords.y(), m_currentDepth) ||
                    forceOpen(newCoords.x() + 1, newCoords.y(), m_currentDepth) ||
                    forceOpen(newCoords.x() - 1, newCoords.y() + 1, m_currentDepth) ||
                    forceOpen(newCoords.x(), newCoords.y() + 1, m_currentDepth) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() + 1, m_currentDepth) ||

                    // Bottom

                    forceOpen(newCoords.x() - 1, newCoords.y() - 1, m_currentDepth + 1) ||
                    forceOpen(newCoords.x(), newCoords.y() - 1, m_currentDepth + 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() - 1, m_currentDepth + 1) ||
                    forceOpen(newCoords.x() - 1, newCoords.y(), m_currentDepth + 1) ||
                    forceOpen(newCoords.x(), newCoords.y(), m_currentDepth + 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y(), m_currentDepth + 1) ||
                    forceOpen(newCoords.x() - 1, newCoords.y() + 1, m_currentDepth + 1) ||
                    forceOpen(newCoords.x(), newCoords.y() + 1, m_currentDepth + 1) ||
                    forceOpen(newCoords.x() + 1, newCoords.y() + 1, m_currentDepth + 1);

            if(fail) {
                freeze(true);
                emit gameFailed();
            }
        }

        // Если попали на бомбу, игра окончена :(
        if(selected.isBomb()) {
            freeze(true);
            emit gameFailed();
        } else {
            openCell(newCoords.x(), newCoords.y(), m_currentDepth);
        }
    }

    // При нажатии ПКМ
    if(event->button() == Qt::RightButton) {

        // Выделяем клетку флажком или снимаем выделение
        if(!selected.opened()) {
            bool mark = selected.invertMark();
            emit cellMarked(mark ? ++m_markedCells : --m_markedCells);
        }
    }

    // Перерисовываем виджет
    this->update();
}

void MineField::mouseMoveEvent(QMouseEvent *event) {

    if(!m_highlight)
        return;

    // Проверка на границы поля и на заморозку
    if(        event->pos().x() > fullWidth() + getPositionOffset().x() - 1
            || event->pos().x() < getPositionOffset().x()
            || event->pos().y() > fullHeight() + getPositionOffset().y() - 1
            || event->pos().y() < getPositionOffset().y()) {
        update();
        m_highlightX = -1;
        m_highlightY = -1;
    } else {
        m_highlightX = (event->pos() - getPositionOffset()).x() / m_cellSize;
        m_highlightY = (event->pos() - getPositionOffset()).y() / m_cellSize;
        update();
    }



}


