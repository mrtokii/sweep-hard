#include <QFile>
#include <QDebug>
#include <QStringList>

#include "qstylesheet.h"

QStyleSheet::QStyleSheet(QObject *parent) :
    QObject(parent),
    m_styleSheet("")
{

}

QStyleSheet::QStyleSheet(QString path, QObject *parent) :
    QObject(parent),
    m_styleSheet("")
{
    loadFromFile(path);
}

bool QStyleSheet::loadFromFile(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_styleSheet = file.readAll();
        return true;
    }
    else
    {
        QString error = file.errorString();
        return false;
    }

}

QString QStyleSheet::style()
{
    return m_styleSheet;
}
