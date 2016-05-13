#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sidePanel->setAlignment(Qt::AlignBottom);

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
    delete m_gameManager;
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
    msgBox.setText("Minesweeper V1.20 UWP (160513).\nMade by mrtokii. \nI dedicate this great game to my programming teacher, who is probably in Metro now...");
    msgBox.exec();
}

void MainWindow::on_recordsButton_clicked()
{
    m_gameManager->showRecords();
}
