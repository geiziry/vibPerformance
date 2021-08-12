#include <QtTest>


class spectrumCalcService:public QObject
{
    Q_OBJECT
//public:
//    spectrumCalcService() {}
//    ~spectrumCalcService();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void sgy_fftw();


};
void spectrumCalcService::initTestCase()
{

}

void spectrumCalcService::cleanupTestCase()
{

}

void spectrumCalcService::sgy_fftw()
{
    int i=0;
    auto v=i+5;
}

//QTEST_MAIN(spectrumCalcService)

#include "tst_spectrumcalcservice.moc"
