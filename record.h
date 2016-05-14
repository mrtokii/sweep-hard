#ifndef RECORD_H
#define RECORD_H
#include<QTime>
#include<QString>


class Record
{
    QTime m_time;
    QString m_who;

public:
    Record();
    Record(QTime time, QString who);

    QTime time() const { return m_time; }
    QString who() const { return m_who; }

    QString compact() const;
};

#endif // RECORD_H
