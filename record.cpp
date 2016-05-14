#include "record.h"

#include <QDebug>

Record::Record() :
    m_time(QTime()),
    m_who("") {

}

Record::Record(QTime time, QString who) :
    m_time(time),
    m_who(who) {

}

QString Record::compact() const
{
    QString sep = "||";

    int time = -m_time.msecsTo(QTime(0, 0, 0));

    return ( QString::number(time) + sep + who() );
}
