#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setField(MineField *field) {
    m_field = field;
    QObject::connect(m_field, SIGNAL(cellOpened(int)), this->ui->spinBoxBombs, SLOT(setValue(int)));
}

void MainWindow::on_generateField_clicked()
{
    if(ui->spinBoxBombs->value() < ui->spinBoxHeight->value() * ui->spinBoxWidth->value()) {
        m_field->setProperties(ui->spinBoxHeight->value(), ui->spinBoxWidth->value(), ui->spinBoxBombs->value());
    } else {
        QMessageBox msgBox;
        msgBox.setText("Too many bombs for this field!");
        msgBox.exec();
    }

}
