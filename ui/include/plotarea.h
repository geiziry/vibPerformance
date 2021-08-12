#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>
#include <QtCharts>

using namespace QtCharts;

namespace Segy {
class data;
}

namespace Ui {
class plotArea;
}

class plotArea : public QWidget
{
    Q_OBJECT

public:
    explicit plotArea(QWidget *parent = nullptr);
    ~plotArea();
public slots:
    void openSelectedSgyFiles(QStringList indexes);
    void plotTraceIndex(int index);
signals:
    void setTraceIndexRange(int,int);
    void calcSpectrum(QList<QPointF>,int);
private:
    Ui::plotArea *ui;
    int openSgyFile(const QString &filepath);
    void prepareChart(QChartView * chartview, Segy::data *sgyfile, QList<QPointF> points);
    void setSgyFileLblTxt(const QString& dir);
    QSet<Segy::data*> m_sgyfiles;
};

#endif // PLOTAREA_H
