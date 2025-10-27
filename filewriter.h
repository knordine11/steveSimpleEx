#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class filewriter : public QObject
{
    Q_OBJECT
public:
    explicit filewriter(QObject *parent = nullptr);

    static void WriteData();

signals:
};

#endif // FILEWRITER_H
