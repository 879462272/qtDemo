#include "contralseriesport.h"
#include<QDebug>
#include<QByteArray>
#include<QString>
WorkSeriesPort::WorkSeriesPort(QObject*parent):QObject(parent),m_SeriesPort(this) //这里给他初始化一个this指针，
                                                                                  //指明this是m_SeriesPort 对象，后面跟着进行movetothread
{
    qDebug()<<"WorkSeriesPort 构造函数 线程id"<<QThread::currentThread();
    m_WorkThread=new QThread;
    inIntSlots();
    this->moveToThread(m_WorkThread);
    qDebug()<<"startbefone"<<m_SeriesPort.thread()->currentThread();

    m_WorkThread->start();
    qDebug()<<"startafter"<<m_SeriesPort.thread()->currentThread();
    connect(&m_SeriesPort,&QSerialPort::readyRead,[=](){
         emit sigSendBuf(m_SeriesPort.readAll());
    });


}

WorkSeriesPort::~WorkSeriesPort()
{
    qDebug()<<"~WorkSeriesPort openSeriesPort 线程id"<<QThread::currentThread();

    if(m_SeriesPort.isOpen()){
        m_SeriesPort.waitForBytesWritten();
        m_SeriesPort.close();
    }
    // 断开线程
    m_WorkThread->exit();
}

int32_t WorkSeriesPort::openSeriesPort(QString PortName,int BaudRate,int DataBit,int Parity,int StopBits)
{

    qDebug()<<"WorkSeriesPort openSeriesPort 线程id"<<QThread::currentThread();

       m_SeriesPort.setPortName(PortName);
       m_SeriesPort.setBaudRate(BaudRate);
       m_SeriesPort.setDataBits((QSerialPort::DataBits)DataBit);
       m_SeriesPort.setParity((QSerialPort::Parity)Parity);
       m_SeriesPort.setStopBits((QSerialPort::StopBits)StopBits);
       m_SeriesPort.setFlowControl(QSerialPort::NoFlowControl);
       bool ret= m_SeriesPort.open(QIODevice::ReadWrite);
       if(ret){
           qDebug()<<"打开成功";
       }
       return m_SeriesPort.error();
}

int32_t WorkSeriesPort::closeSeriesPort()
{
    qDebug()<<"WorkSeriesPort closeSeriesPort 线程id"<<QThread::currentThread();

    // 关闭串口
    m_SeriesPort.waitForBytesWritten();
    m_SeriesPort.close();
    return m_SeriesPort.error();
}



int32_t WorkSeriesPort::Write(bool hex,QString str)
{
    qDebug()<<"WorkSeriesPort Write 线程id"<<QThread::currentThread();

    if(hex){

        //将16进制 表示的 QString 转换成对应的byte 数据

            QByteArray byte_arr;
            bool ok;
            //如果str的长度 不是2的倍数  那么直接返回空

            int len=str.size();
            for(int i=0;i<len;i+=2){
                 byte_arr.append(char(str.mid(i,2).toUShort(&ok,16)));
            }
            m_SeriesPort.write(byte_arr);
        }else{
      m_SeriesPort.write(str.toLatin1());
    }
    return m_SeriesPort.error();
}

int32_t WorkSeriesPort::delThis()
{
 m_WorkThread->exit();
 return 1;
}

void WorkSeriesPort::inIntSlots()
{
    QObject::connect(m_WorkThread,&QThread::finished,this,&WorkSeriesPort::deleteLater);
    QObject::connect(m_WorkThread,&QThread::finished,m_WorkThread,&QThread::deleteLater);
}


