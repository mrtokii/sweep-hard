#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sidePanel->setAlignment(Qt::AlignBottom);
    //ui->sidePanel->addStretch(1);


    m_gameManager = new GameManager();
    MineField *field = new MineField();

    m_gameManager->connectField(field);
    m_gameManager->connectTimer(ui->timerLabel);
    m_gameManager->connectInfoPanel((ui->infoLabel));

    ui->fieldPlace->addWidget(field);

    m_gameManager->newGame(GameManager::easy);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setField(MineField *field) {
    m_field = field;
}

void MainWindow::on_generateField_clicked()
{
    m_gameManager->newGame();

}

void MainWindow::on_aboutButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Сапёр V1.00 (160327).\n Сделано mrtokii.");
    msgBox.exec();
}
