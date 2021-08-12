#include "spectrumcalcservice.h"
#include <cmath>

#define REAL 0
#define IMAG 1

/*!
 * \brief spectrumCalcService::fft
 * caculates the fft magnitude, log magnitude, angle (phase), freq at each point
 * and pack them in vector of tuples (mag,log_mag,angle,freq)
 * \param points QList of QPointF
 * \return vector of tuples (mag,log_mag,angle,freq)
 */
std::vector<FFT_OUT> spectrumCalcService::fft(QList<QPointF> points)
{
    std::vector<FFT_OUT>fft_out;
    //define the length of the complex array
    int n=points.length();

    fftw_complex x[n],y[n]; //this is equivalent to: double x[n][2];

    fill_fft_input(x,points,n);
    fftw_plan plan=fftw_plan_dft_1d(n,x,y,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(plan);
    fill_fft_output(y,n,fft_out);

    fftw_destroy_plan(plan);
    fftw_cleanup();

    return fft_out;
}

/*!
 * \brief spectrumCalcService::fill_fft_vector
 * fills the output vector of tuples with the result output of the fft
 * \param y output of the fft
 * \param n total number of samples
 * \param fft_out  return vector of tuples passed by reference
 */
void spectrumCalcService::fill_fft_output(const fftw_complex * y,int n, std::vector<FFT_OUT> &fft_out)
{
    for (int i=0;i<n/2;i++) {
        auto real=y[i][REAL], imag=y[i][IMAG];
        auto mag=sqrt(pow(real,2)+pow(imag,2));
        auto log_mag=10*log10(mag);
        auto angle=atan(real/imag)*M_PI/180;
        //freq calc according to https://stackoverflow.com/a/4371627
        auto freq = i/(0.002*n); // 0.002 here is sampling interval dt (المفروض تكون parameter)
        fft_out.push_back(std::make_tuple(mag,log_mag,angle,freq));
    }

}
/*!
 * \brief spectrumCalcService::fill_fft_input
 * fills the input fftw_complex array with values from list of trace sample points
 * \param x  input fftw_complex array passed by reference as pointer
 * \param points list of trace samples as QList<QPointF>
 * \param n count of trace samples
 */
void spectrumCalcService::fill_fft_input(fftw_complex* x,QList<QPointF> points,int n)
{
    for (int i=0;i<n-1;i++) {
        x[i][REAL]=points[i+1].y()/n; //divide by n for normalization مش أكيد
        x[i][IMAG]=0;
    }
}
