#ifndef DATA_H
#define DATA_H

#include "segyio/segy.h"
#include <QObject>
#include <QPointF>

class QFile;

namespace Segy {
class data : public QObject
{
    Q_OBJECT
public:
    explicit data(const QString &sgyFile,QObject *parent = nullptr);
    ~data();
    int no_samples();
    QString FilePath();
    bool FileExist();
    std::pair<float,float>MinMaxtrValue()const;
    int TraceCount();

public slots:
    QList<QPointF> getTraceByIdx(int idx);

private:
    void setMinMaxtrValue(float* trbuf);
    int m_nsamples;
    int m_format;
    int *m_trace_count;
    int m_trace_bsize;
    long m_trace0;
    char m_header[ SEGY_BINARY_HEADER_SIZE ];
    std::pair<float,float> m_minmax;
    QFile *m_file;
    bool m_file_exist;
    segy_file* fp;
};
}
#endif // DATA_H
