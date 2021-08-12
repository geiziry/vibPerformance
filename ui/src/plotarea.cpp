#include "plotarea.h"
#include "ui_plotarea.h"
#include "data.h"
#include "util.h"

plotArea::plotArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plotArea)
{
    ui->setupUi(this);
}

plotArea::~plotArea()
{
    delete ui;
}

/*!
 * \brief opens a sgy file, and plots first 3 traces in separate three plots
 */
void plotArea::openSelectedSgyFiles(QStringList indexes)
{
    //clear any previously added sgy files
    m_sgyfiles.clear();
    qDeleteAll(m_sgyfiles.begin(),m_sgyfiles.end());
    //browse to file to get full path
    if(indexes.isEmpty())return;

    setSgyFileLblTxt(indexes.first());

    QList<int> trCounts;
    for(auto filepath:indexes){
        auto trCount= openSgyFile(filepath);
        if(trCount<0)continue;
        trCounts.append(trCount);
    }
    auto min=*std::min_element(trCounts.begin(),trCounts.end());
    emit setTraceIndexRange(0,min-1);
    //plots the first trace in each file
    plotTraceIndex(0);
}
/*!
 * \brief plots the traces from the first 3 sgyfiles selected according to the selected index
 * connected to the QSpinBox::valueChanged signal of the trace index spinbox
 * \param index
 */
void plotArea::plotTraceIndex(int index)
{
    for (int i = 0;i<m_sgyfiles.size() && i < 3; ++i) {
        auto sgyfile=m_sgyfiles.values()[i];
        auto points=sgyfile->getTraceByIdx(index);
        auto chart=this->findChild<QChartView*>(QString("sgyPlot%1").arg(i+1));
        prepareChart(chart,sgyfile,points);
        emit calcSpectrum(points,i);
    }
}

/*!
 * \brief opens dialog to select a segy file
 * \return int to indicate whether a file is selected or not
 */
int plotArea::openSgyFile(const QString & filepath)
{
    if(filepath.isEmpty())
        return -1;
    auto sgyfile=new Segy::data(filepath,this);
    if (!sgyfile->FileExist()) {
        return -1;
    }
    m_sgyfiles.insert(sgyfile);
    return sgyfile->TraceCount();
}

/*!
 * \brief adds lineSeries to chart and reset scale
 * \param chartview chart to add to
 * \param points series to plot
 * \param title chart title
 */
void plotArea::prepareChart(QChartView *chartview, Segy::data *sgyfile, QList<QPointF> points)
{
    chartview->chart()->removeAllSeries();
    auto chart=chartview->chart();
    chart->legend()->setVisible(false);

    auto series=new QLineSeries();
    series->replace(points);
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
    yaxis->setLabelFormat("%.0F");

    chart->setTitle(sgyfile->FilePath());
    chartview->setRenderHint(QPainter::Antialiasing);
}

/*!
 * \brief sets the sgylbl under the centralwidget to dir
 * \param dir dir of the first selected sgy file from the indexes
 */
void plotArea::setSgyFileLblTxt(const QString &dir)
{
    auto lbl=shared::parentByName(this,"centralWidget")
            ->findChild<QLabel*>("sgyFilelbl");
    if(lbl!=nullptr){
        QFileInfo inf(dir);
        lbl->setText(inf.path());
    }

}
