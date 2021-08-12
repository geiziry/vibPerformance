#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>
#include "data.h"
#include <eigen3/Eigen/Dense>
#include "spectrumcalcservice.h"
#include "xcorr.h"

using namespace Segy;

class open_sgy_data : public QObject
{
    Q_OBJECT

public:
    open_sgy_data();
    ~open_sgy_data();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void sgy_file_not_exist();
    void sgy_file_exist();
    void sgy_file_fake();
    void sgy_fft();
    void sgy_fft_xcor();
    void test_eigen();
private:
    QString m_curr_path;
    QString m_testdata_path;
    spectrumCalcService* specCalacService;
};

open_sgy_data::open_sgy_data():
    m_curr_path(QDir::currentPath()),
    specCalacService(new spectrumCalcService () )
{
    m_testdata_path=m_curr_path+"/testdata/";
}

open_sgy_data::~open_sgy_data()
{

}

void open_sgy_data::initTestCase()
{

}

void open_sgy_data::cleanupTestCase()
{

}

void open_sgy_data::sgy_file_not_exist()
{
    auto filepath=m_curr_path+"hgf.segy";
    data *file=new data(filepath,nullptr);
    QVERIFY(file->FileExist()==false);
    delete file;
}

void open_sgy_data::sgy_file_exist()
{
    data *file=new data(m_testdata_path+"Run 1_NASCENT_SOURCE_S1_for_Segy.segy",nullptr) ;
    auto points=file->getTraceByIdx(0);
    QVERIFY(points.size()==8500);
    delete file;
}

void open_sgy_data::sgy_file_fake()
{
    data *file=new data(m_testdata_path+"fake.segy",nullptr) ;
    auto points=file->getTraceByIdx(0);
    QVERIFY(points.size()==0);
    delete file;

}

void open_sgy_data::sgy_fft()
{
    data *file=new data(m_testdata_path+"Run 1_NASCENT_SOURCE_S1_for_Segy.segy",nullptr) ;
    auto points=file->getTraceByIdx(0);
    specCalacService->fft(points);

}

void open_sgy_data::sgy_fft_xcor()
{
    data *file=new data(m_testdata_path+"Run 1_NASCENT_SOURCE_S1_for_Segy.segy",nullptr) ;
    auto y_points=file->getTraceByIdx(0);
    auto x_points=file->getTraceByIdx(0);
    int n=x_points.length();
    fftw_complex x[n],y[n],result[n];

    specCalacService->fill_fft_input(x,x_points,x_points.length());
    specCalacService->fill_fft_input(y,y_points,y_points.length());

    xcorr(x,y,result,x_points.length());

}

double simple_function(Eigen::VectorXd &va, Eigen::VectorXd &vb){
    double d=va.dot(vb);
    return d;
}

void open_sgy_data::test_eigen()
{
    int len=1000000;
    int num_repititions=100;

    Eigen::VectorXd va=Eigen::VectorXd::Random(len);
    Eigen::VectorXd vb=Eigen::VectorXd::Random(len);

    double result;
    using Duration = std::chrono::system_clock::duration;
    auto start=std::chrono::system_clock::now();
    for (auto i=0;i<num_repititions;i++) {
        result=simple_function(va,vb);
    }
    auto end=std::chrono::system_clock::now();
    auto elapsed_seconds=end-start;

    qDebug()<<"result: "<<result;
    qDebug()<<"elapsed seconds: "<<static_cast<double>(elapsed_seconds.count())/Duration::period::den;
}


QTEST_MAIN(open_sgy_data)

#include "tst_open_sgy_data.moc"
