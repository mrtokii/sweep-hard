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

    setField(field);

    m_gameManager->connectField(field);
    m_gameManager->connectTimer(ui->timerLabel);
    m_gameManager->connectInfoPanel((ui->infoLabel));

    ui->fieldPlace->addWidget(field);

    m_gameManager->newGame(GameManager::easy);

    updateHud();
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

void MainWindow::updateHud()
{
    auto currentDepth = m_field->currentDepth() + 1;
    auto depth = m_field->depth();

    auto descriptionText = QString("(%0/%1)").arg(currentDepth).arg(depth);

    ui->levelDepth->setText(descriptionText);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_PageDown:
        if(m_field->currentDepth() > 0)
            m_field->setCurrentDepth(m_field->currentDepth() - 1);
        break;

    case Qt::Key_PageUp:
        if(m_field->currentDepth() < m_field->depth() - 1)
            m_field->setCurrentDepth(m_field->currentDepth() + 1);
        break;

    default:
        break;
    }

    updateHud();
}
