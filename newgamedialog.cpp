#include "newgamedialog.h"
#include "ui_newgamedialog.h"

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

}

void NewGameDialog::on_startMedium_clicked()
{

}

void NewGameDialog::on_startHard_clicked()
{

}

void NewGameDialog::on_startCustom_clicked()
{

}
