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

void QStyleSheet::addVariable(QString var, QString value)
{
    m_replacements.insert(var, value);
}

QString QStyleSheet::style()
{
    QString styleSheet = m_styleSheet;

    int blockStart = 0, blockEnd = 0;

    // Вырезание блоков комментариев
		while(int commentStart = styleSheet.indexOf("/*", 0) + 1)
    {
        commentStart--;
				int commentEnd = styleSheet.indexOf("*/", commentStart) + 2;
        styleSheet.remove(commentStart, commentEnd - commentStart);
    }

    // Определение границ блока переменных
    blockStart = styleSheet.indexOf("{", styleSheet.indexOf("VARS")) + 1;
    blockEnd = styleSheet.indexOf("}", blockStart); 

    if(blockEnd < 0 || blockStart < 0)
        return QString();

    // Разделение комманд
    QString block = styleSheet.mid(blockStart, blockEnd - blockStart);
    QStringList commands = block.trimmed().split(";", QString::SkipEmptyParts);

    // Добавление переменных
    for(int i = 0; i < commands.length(); i++)
    {
        QStringList rpls = commands.at(i).trimmed().split(":", QString::SkipEmptyParts);
		if(rpls.count() == 2)
			addVariable(rpls.at(0).trimmed(), rpls.at(1).trimmed());
    }

    // Замена переменных в стилях на значения
    QMap<QString,QString>::iterator it = m_replacements.begin();
    for(;it != m_replacements.end(); ++it)
    {
        styleSheet.replace("@" + it.key() + " ", it.value() + " ");
        styleSheet.replace("@" + it.key() + ";", it.value() + ";");
        styleSheet.replace("@" + it.key() + ",", it.value() + ",");
        styleSheet.replace("@" + it.key() + ".", it.value() + ".");
    }

    return styleSheet;
}
