#ifndef SPECTRUMCALC_H
#define SPECTRUMCALC_H

#include <QWidget>
#include <QtCharts>

using namespace QtCharts;

typedef  std::tuple<double,double,double,double> FFT_OUT;

namespace Ui {
class spectrumCalc;
}

class spectrumCalcService;

class spectrumCalc : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumCalc(QWidget *parent = nullptr);
    ~spectrumCalc();
public slots:
    void processSpecCalc(QList<QPointF> points, int index);
private:
    Ui::spectrumCalc *ui;
    spectrumCalcService *specCalc;
    void prepareChart(QChartView *chartview, QLineSeries *series, int lbl_format=0);
};

#endif // SPECTRUMCALC_H
