#include "newgamedialog.h"
#include "ui_newgamedialog.h"

#include <QMessageBox>

NewGameDialog::NewGameDialog(GameManager *gm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
    m_gm = gm;
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}



void NewGameDialog::on_startEasy_clicked()
{
    m_gm->newGame(GameManager::easy);
    accept();
}

void NewGameDialog::on_startMedium_clicked()
{
    m_gm->newGame(GameManager::medium);
    accept();
}

void NewGameDialog::on_startHard_clicked()
{
    m_gm->newGame(GameManager::hard);
    accept();
}

void NewGameDialog::on_startCustom_clicked()
{
    int w = ui->customWidth->value();
    int h = ui->customHeight->value();
    int b = ui->customBombs->value();

    if(b < w*h-9) {
        m_gm->newGame(w, h, b);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Неправильные настройки для поля: слишком много бомб!");
        msgBox.exec();
    }

    accept();
}
