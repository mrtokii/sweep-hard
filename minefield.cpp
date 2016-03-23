#include "minefield.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTime>

void MineField::placeBombs(int amount, int startX, int startY)
{
    // Разбуриваем генератор случайных чисел
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    for(int i = 0; i < amount;) {
        // Генерируем случайные координаты
        int randomY = qrand() % m_height;
        int randomX = qrand() % m_width;


        // Проверка на то, чтобы рядом со стартовой позицией
        // не было бомб
        bool bombAround = randomX >= startX-1 && randomX <= startX+1
                && randomY >= startY-1 && randomY <= startY+1;


        if(!bombAround && !m_field[randomY][randomX].isBomb())
        {
            // Размещаем бомбу
            m_field[randomY][randomX].setContents(9);
            i++;
        }

    }
}

void MineField::createField()
{
    // Создаем массив клеток...
    m_field = QVector< QVector< Cell > >(m_height);

    // ...и заполняем пустыми клетками
    for(int i = 0; i < m_height; i++) {
        m_field[i] = QVector< Cell >(m_width);
    }

    m_openedCells = 0;
    m_markedCells = 0;
    emit gamePrepared();

    freeze(false);
    emit cellMarked(0);
    update();
}

void MineField::openCell(int x, int y)
{
    // Проверка на попадание в поле
    if(x >= 0 && x < m_width && y >= 0 && y < m_height) {

        // Ссылка на текущую клетку
        Cell &current = m_field[y][x];

        // Проверка на то, стоит ли ее открывать     

        if(!current.opened() && !current.isBomb()) {

            // Безопасно удаляем флажок, если он стоит на клетке
            if(current.marked())
                emit cellMarked(--m_markedCells);

            // Открываем клетку и сигналим всем об этом
            current.open();
            emit cellOpened(++m_openedCells);

            // Если клетка пустая, открываем все соседние клетки
            if(empty(x, y)) {
                openCell(x - 1, y - 1);
                openCell(x, y - 1);
                openCell(x + 1, y - 1);
                openCell(x - 1, y);
                openCell(x + 1, y);
                openCell(x - 1, y + 1);
                openCell(x, y + 1);
                openCell(x + 1, y + 1);

            // Если не пустая, открываем пустые рядом
            } else {
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

bool MineField::forceOpen(int x, int y)
{
    if(x >= 0 && x < m_width && y >= 0 && y < m_height) {
        if(m_field[y][x].marked() || m_field[y][x].opened())
            return false;

        openCell(x, y);
        if(m_field[y][x].isBomb())
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
    m_height = 1;
    m_width = 1;
    m_bombs = 1;

    setCellSize(50);
    setProperties(9, 9, 10);
    clearMessageText();
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

void MineField::showBombs()
{
    // Ссылка на текущую клетку
    Cell *current;

    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            current = &m_field[i][j];
            if(current->isBomb())
                current->showBomb();
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

    // Начинаем рисовать!
    QPainter painter(this);
    painter.fillRect(QRect(0, 0, size().width(), size().height()), QColor(43, 43, 43));

    painter.translate(getPositionOffset());



    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            painter.drawPixmap(j * m_cellSize, i * m_cellSize, m_cellSize, m_cellSize, m_field[i][j].draw());
        }
    }

    if(m_messageText != "") {
        QFont font("times", 32);
        QFontMetrics fm(font);
        int pixelsWide = fm.width(m_messageText);
        int pixelsHigh = fm.height();
        QRect r = fm.boundingRect(m_messageText);
        r += QMargins(5, 5, 5, 5);

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

    // Ссылка на выбранную ячейку
    Cell &selected = m_field[newCoords.y()][newCoords.x()];

    // При нажатии ЛКМ
    if (event->button() == Qt::LeftButton && !selected.marked()) {

        // Начало игры, если ни одной ячейки еще не открыто
        if(!m_openedCells) {
            generateField(newCoords.x(), newCoords.y());
            emit gameStarted();
        }

        if(selected.opened()) {
            bool fail =
                   forceOpen(newCoords.x() - 1, newCoords.y() - 1) ||
                   forceOpen(newCoords.x(), newCoords.y() - 1) ||
                   forceOpen(newCoords.x() + 1, newCoords.y() - 1) ||
                   forceOpen(newCoords.x() - 1, newCoords.y()) ||
                   forceOpen(newCoords.x() + 1, newCoords.y()) ||
                   forceOpen(newCoords.x() - 1, newCoords.y() + 1) ||
                   forceOpen(newCoords.x(), newCoords.y() + 1) ||
                   forceOpen(newCoords.x() + 1, newCoords.y() + 1);

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
            openCell(newCoords.x(), newCoords.y());
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


