#include "filewriter.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

filewriter::filewriter(QObject *parent)
    : QObject{parent}
{}

void filewriter::WriteData()
{
    QFile file("rec_data.txt");

    if(!file.exists())
    {
        qInfo() << "file not found";        
    }
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical("Open failed");
        return;
    }
    QString temp = QString::number(rec_arr_cnt);
    qDebug() << "In Writer" << temp;
    const char *temp2;
    temp2 = temp.toLocal8Bit().constData();
    file.write("rec_arr_cnt = ");
    file.write(temp2);
    qDebug() << "written...";
    file.close();
}
