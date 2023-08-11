#ifndef CUSTOMSERIESPORT_H
#define CUSTOMSERIESPORT_H

#include <QObject>
#include <QSerialPort>
#include <QThread>


class WorkSeriesPort :public QObject
{
   Q_OBJECT
public:
    WorkSeriesPort(QObject*parent=nullptr);
    ~WorkSeriesPort();
public:
    int32_t openSeriesPort(QString PortName,int BaudRate, int DataBits, int Parity, int StopBits);

    int32_t closeSeriesPort();

    int32_t Write(bool hex,QString str);

    int32_t delThis();

  //  void* retSerialPort(){return static_cast<void*>(&m_SeriesPort);};
private:
    void inIntSlots();
signals:
    void sigSendBuf(QByteArray arr);
private:
    QThread* m_WorkThread;
    QSerialPort m_SeriesPort;
    bool m_hex=false;
};

#endif // CUSTOMSERIESPORT_H
