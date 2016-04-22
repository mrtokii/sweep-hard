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
    void addVariable(QString var, QString value);
    QString style();


private:
    QString m_styleSheet;
    QMap<QString, QString> m_replacements;

};

#endif // QSTYLESHEET_H
