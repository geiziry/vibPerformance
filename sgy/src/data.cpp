#include "data.h"

#include <QFileDialog>
#include "util.h"
#include <QFile>

Segy::data::data(const QString &sgyFile,QObject *parent)
    : QObject(parent),
      m_nsamples(0),
      m_trace_count(new int()),
      m_file(new QFile(sgyFile))
{
    m_file_exist=m_file->exists() && m_file->open(QIODevice::ReadOnly);
    if(!m_file_exist)
        return;
    fp=segy_open(sgyFile.toStdString().c_str(),"rb");
    segy_binheader( fp, m_header );
    m_format = segy_format( m_header );
    m_nsamples = segy_samples( m_header );
    m_trace0 = segy_trace0( m_header );
    m_trace_bsize = segy_trace_bsize( m_nsamples );
    segy_traces(fp,m_trace_count,m_trace0,m_trace_bsize);

}

Segy::data::~data()
{
    if(m_file_exist)
        segy_close(fp);
    delete m_trace_count;
}

int Segy::data::no_samples()
{
    return m_nsamples;
}

QString Segy::data::FilePath()
{
    return m_file->fileName();
}

bool Segy::data::FileExist()
{
    return m_file_exist;
}

std::pair<float, float> Segy::data::MinMaxtrValue() const
{
    return m_minmax;
}

int Segy::data::TraceCount()
{
    return *m_trace_count;
}

QList<QPointF> Segy::data::getTraceByIdx(int idx)
{
    QList<QPointF>list;
    if(*m_trace_count==0)return list;

    float* trbuf = new float[m_trace_bsize];

    char traceh[ SEGY_TRACE_HEADER_SIZE ];
    segy_traceheader( fp, idx, traceh, m_trace0, m_trace_bsize );
    segy_readtrace( fp, idx, trbuf, m_trace0, m_trace_bsize );
    segy_to_native(m_format,m_nsamples,trbuf);

    setMinMaxtrValue(trbuf);

    for (int j=0;j<m_nsamples;++j) {
        list.append(QPointF(j,trbuf[j]));
    }
    delete[] trbuf;
    return list;
}

void Segy::data::setMinMaxtrValue(float *trbuf)
{
    auto minmax=std::minmax_element(trbuf,trbuf+m_nsamples);
    m_minmax=std::make_pair(shared::roundToThousandths(*minmax.first),
                            shared::roundToThousandths(*minmax.second));
}



