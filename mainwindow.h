#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "minefield.h"
#include "gamemanager.h"
#include "recordsdialog.h"

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

    void on_recordsButton_clicked();

    void updateHud();

private:
    Ui::MainWindow *ui;
    MineField *m_field;

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H
