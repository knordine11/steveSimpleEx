#include "widget.h"
#include <QApplication>

#define ARR_SIZE 48000
double rec_arr[ARR_SIZE];
int arr_size = ARR_SIZE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
