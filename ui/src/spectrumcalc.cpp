#include "spectrumcalc.h"
#include "ui_spectrumcalc.h"
#include "spectrumcalcservice.h"

spectrumCalc::spectrumCalc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumCalc),
    specCalc(new spectrumCalcService())
{
    ui->setupUi(this);

}

spectrumCalc::~spectrumCalc()
{
    delete ui;
}

/*!
 * \brief spectrumCalc::processSpecCalc
 * \param points
 * \param index
 */
void spectrumCalc::processSpecCalc(QList<QPointF> points,int index)
{
    auto mag_series=new QLineSeries(),
         log_series=new QLineSeries(),
         angle_series=new QLineSeries();
    double mag,log_mag,angle,freq;
    foreach (auto fft_out, specCalc->fft(points)) {
        std::tie(mag,log_mag,angle,freq)=fft_out;
        mag_series->append(freq,mag);
        log_series->append(freq,log_mag);
        angle_series->append(freq,angle);
    }

    auto mag_chart=this->findChild<QChartView*>(QString("s%1_mag").arg(index+1));
    prepareChart(mag_chart,mag_series);
    auto logmag_chart=this->findChild<QChartView*>(QString("s%1_logmag").arg(index+1));
    prepareChart(logmag_chart,log_series);
    auto phase_chart=this->findChild<QChartView*>(QString("s%1_phase").arg(index+1));
    prepareChart(phase_chart,angle_series,2);
}

/*!
 * \brief spectrumCalc::prepareChart
 * \param chartview
 * \param series
 * \param lbl_format
 */
void spectrumCalc::prepareChart(QChartView *chartview, QLineSeries *series,int lbl_format)
{
    chartview->chart()->removeAllSeries();
    auto chart=chartview->chart();
    chart->legend()->setVisible(false);
    series->setUseOpenGL(true);
    chart->addSeries(series);

    chart->createDefaultAxes();
    //set range and ticks
    if(chart->axes().isEmpty())return;
    auto xaxis=static_cast<QValueAxis*>(chart->axes(Qt::Horizontal).back());
    auto yaxis=static_cast<QValueAxis*>(chart->axes(Qt::Vertical).back());
    xaxis->applyNiceNumbers();
    xaxis->setLabelFormat("%.0F");
    yaxis->applyNiceNumbers();
    yaxis->setLabelFormat(QString("%.%1F").arg(lbl_format));

    chartview->setRenderHint(QPainter::Antialiasing);

}
