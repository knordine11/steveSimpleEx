#ifndef FFTWSTUFF_H
#define FFTWSTUFF_H

#include <QObject>
#include "fftw3/fftw3.h"
#include <cmath>

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class fftwStuff : public QObject
{
    Q_OBJECT
public:
    explicit fftwStuff(QObject *parent = nullptr);
    static void DoIt(int frame_start, int length);
    static double abs(fftw_complex);
    static double bin_freq(size_t, size_t, double);

signals:
};

#endif // FFTWSTUFF_H
