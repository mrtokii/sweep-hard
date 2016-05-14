#include "recordsdialog.h"
#include "ui_recordsdialog.h"

#include <QMessageBox>

void RecordsDialog::createTable(QVector<Record> *source, QTableWidget *dest)
{
    for (int i = 0, s = source->size(); i < s; ++i) {
        dest->setRowCount(dest->rowCount() + 1);
        QTableWidgetItem *time = new QTableWidgetItem(source->at(i).time().toString("mm:ss"));
        QTableWidgetItem *who = new QTableWidgetItem(source->at(i).who());

        dest->setItem(i, 0, time);
        dest->setItem(i, 1, who);
    }
}

RecordsDialog::RecordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordsDialog)
{
    ui->setupUi(this);
}

RecordsDialog::RecordsDialog(QVector<Record>* ee,
                             QVector<Record>* mm,
                             QVector<Record>* hh, QWidget *parent) :
    RecordsDialog(parent)
{
    e = ee;
    m = mm;
    h = hh;

    createTable(e, ui->easyTable);
    createTable(m, ui->mediumTable);
    createTable(h, ui->hardTable);
}

RecordsDialog::~RecordsDialog()
{
    delete ui;
}

void RecordsDialog::on_closeButton_clicked()
{
    reject();
}

void RecordsDialog::on_clearRecordsButton_clicked()
{
    int diff = ui->tabWidget->currentIndex();
    QVector<Record> *container;

    switch(diff) {
        case 0:
            container = e;
        break;

        case 1:
            container = m;
        break;

        case 2:
            container = h;
    }

    container->clear();
    accept();
}

void RecordsDialog::on_tabWidget_tabBarClicked(int index)
{
    ui->clearRecordsButton->setText("Clear " + ui->tabWidget->tabText(index));
}
