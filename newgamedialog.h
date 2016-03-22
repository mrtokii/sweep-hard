#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

#include "gamemanager.h"

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

    GameManager *m_gm;

public:
    explicit NewGameDialog(GameManager *gm, QWidget *parent = 0);
    ~NewGameDialog();

private slots:

    void on_startEasy_clicked();

    void on_startMedium_clicked();

    void on_startHard_clicked();

    void on_startCustom_clicked();

private:
    Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H
