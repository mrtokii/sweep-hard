#ifndef QSTYLESHEET_H
#define QSTYLESHEET_H

#include <QObject>
#include <QMap>
#include <QString>

class QStyleSheet : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheet(QString path, QObject *parent = 0);
    explicit QStyleSheet(QObject *parent = 0);

    bool loadFromFile(QString path);
    QString style();


private:
    QString m_styleSheet;

};

#endif // QSTYLESHEET_H
