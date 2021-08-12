#ifndef XCORR_H
#define XCORR_H

#include <fftw3.h>
#include <complex>

void xcorr(fftw_complex *,fftw_complex *,fftw_complex *,int);

#endif // XCORR_H
