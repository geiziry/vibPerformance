#ifndef SPECTRUMCALCSERVICE_H
#define SPECTRUMCALCSERVICE_H
#include <QList>
#include <fftw3.h>

typedef  std::tuple<double,double,double,double> FFT_OUT;


class spectrumCalcService
{
    friend class open_sgy_data;
public:
    std::vector<FFT_OUT> fft(QList<QPointF> points );
private:
    void fill_fft_output(const fftw_complex*, int n, std::vector<FFT_OUT>& fft_out);
    void fill_fft_input(fftw_complex *x, QList<QPointF> points, int n);
};

#endif // SPECTRUMCALCSERVICE_H
