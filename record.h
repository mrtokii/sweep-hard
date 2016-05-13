#ifndef RECORD_H
#define RECORD_H
#include<QTime>
#include<QString>


class Record
{
    QTime m_time;
    QTime m_when;
    QString m_who;

public:
    Record();
    Record(QTime time, QTime when, QString who);

    QTime time() const { return m_time; }
    QTime when() const { return m_when; }
    QString who() const { return m_who; }

    QString compact() const;
};

#endif // RECORD_H
