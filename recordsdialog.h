#ifndef RECORDSDIALOG_H
#define RECORDSDIALOG_H

#include <QDialog>
#include "record.h"
#include <QTableWidget>

namespace Ui {
class RecordsDialog;
}

class RecordsDialog : public QDialog
{
    Q_OBJECT

    QVector<Record> *e, *m, *h;

    void createTable(QVector<Record>* source, QTableWidget* dest);

public:
    explicit RecordsDialog(QWidget *parent = 0);
    explicit RecordsDialog(QVector<Record>* ee,
                           QVector<Record>* mm,
                           QVector<Record>* hh, QWidget *parent = 0);
    ~RecordsDialog();

private slots:
    void on_closeButton_clicked();

private:
    Ui::RecordsDialog *ui;
};

#endif // RECORDSDIALOG_H
