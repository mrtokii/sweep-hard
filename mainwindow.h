#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "minefield.h"
#include "gamemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    GameManager *m_gameManager;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setField(MineField *field);

private slots:
    void on_generateField_clicked();

    void on_aboutButton_clicked();

private:
    Ui::MainWindow *ui;
    MineField *m_field;
};

#endif // MAINWINDOW_H
