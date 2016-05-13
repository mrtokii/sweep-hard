#include "record.h"

#include <QDebug>

Record::Record() :
    m_time(QTime()),
    m_when(QTime()),
    m_who("") {

}

Record::Record(QTime time, QTime when, QString who) :
    m_time(time),
    m_when(when),
    m_who(who) {

}

QString Record::compact() const
{
    QString sep = "||";

    int time = -m_time.msecsTo(QTime(0, 0, 0));
    qDebug() << QTime();
    qDebug() << time;
    int when = m_when.msecsTo(QTime());

    return QString::number(time) +
            sep +
            QString::number(when) +
            sep +
            who();
}
