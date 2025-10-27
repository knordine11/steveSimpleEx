#include "fftwstuff.h"
#include <iostream>
#include "fftw3/fftw3.h"
#include <cmath>
#include <iomanip>
#include <QDebug>



fftwStuff::fftwStuff(QObject *parent)
    : QObject{parent}
{

}

void fftwStuff::DoIt(int frame_start, int length)
{
    std::cout << "starting..." << std::endl;
    fftw_complex* in, * out;
    fftw_plan p;

    const size_t N = 1024;
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    double Fs = 44100.0/64;

    for (size_t i = 0; i < N; i++)
    {
        in[i][0] = rec_arr[frame_start+i]*1000;
        in[i][1] = 0.0;
    }    

    fftw_execute(p);

    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    for (size_t i = 0; i < N; i++)
    {
        if (i > 220 and i < 440)
        {
            std::cout << fftwStuff::bin_freq(i, N, Fs) << " Hz : " << fftwStuff::abs(out[i]) << std::endl;
        }
    }
    std::cout << "rec_arr_cnt: " << rec_arr_cnt << "  length: " << length << std::endl;
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

double fftwStuff::abs(fftw_complex c)
{
    return std::sqrt(c[0] * c[0] + c[1] * c[1]);
}

double fftwStuff::bin_freq(size_t n, size_t Fs, double N)
{
    return n * Fs / N;
}
