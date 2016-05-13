#include "recordsdialog.h"
#include "ui_recordsdialog.h"

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

    /*for (int i = 0, s = e->size(); i < s; ++i) {
        ui->easyTable->setRowCount(ui->easyTable->rowCount() + 1);
        QTableWidgetItem *time = new QTableWidgetItem(e->at(i).time().toString("mm:ss"));
        QTableWidgetItem *who = new QTableWidgetItem(e->at(i).who());

        ui->easyTable->setItem(i, 0, time);
        ui->easyTable->setItem(i, 1, who);
    }*/
}

RecordsDialog::~RecordsDialog()
{
    delete ui;
}

void RecordsDialog::on_closeButton_clicked()
{
    reject();
}
