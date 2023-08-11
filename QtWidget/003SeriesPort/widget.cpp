#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QThread>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    // 因为需要movetothread 所以不给他指定父类指针.
    m_doWork=new WorkSeriesPort;
    qDebug()<<"Widget 构造函数 线程id"<<QThread::currentThread();
    ui->setupUi(this);
    ui->open->setProperty("isOpen",false);
    inIntSlots();

}

Widget::~Widget()
{
    close();
    exit();
    delete ui;
}






void Widget::on_open_clicked()
{
    int ret;
    if(!ui->open->property("isOpen").toBool()){
        ret= emit open(ui->com->currentText(),ui->BaudRate->currentText().toUInt(),ui->DataBit->currentText().toUInt(),ui->Parity->currentText().toUInt(),ui->StopBits->currentText().toUInt());
        if(!ret){
            ui->open->setProperty("isOpen",true);
            ui->open->setText("关闭");
        }
    }else{
        ret= emit close();
        if(!ret){
            ui->open->setProperty("isOpen",false);
            ui->open->setText("打开");
        }
    }
    qDebug()<<"on_open_clicked"<<ret;
}

void Widget::inIntSlots()
{
   auto ret =QObject::connect(this,&Widget::open,m_doWork,&WorkSeriesPort::openSeriesPort);

    ret =QObject::connect(this,&Widget::close,m_doWork,&WorkSeriesPort::closeSeriesPort,Qt::QueuedConnection);
    ret =QObject::connect(this,&Widget::exit,m_doWork,&WorkSeriesPort::delThis,Qt::QueuedConnection);

    ret =QObject::connect(this,&Widget::writredata,m_doWork,&WorkSeriesPort::Write);
    QObject::connect(m_doWork,&WorkSeriesPort::sigSendBuf,this,&Widget::on_read,Qt::QueuedConnection);
}

void Widget::on_send_clicked()
{
 QTextDocument* str= ui->plainTextEdit_2->document();
 QString nStr= str->toPlainText();
 auto ret=emit writredata(ui->Hex->checkState(),nStr);
 qDebug()<<"on_send_clicked"<<ret;
}

void Widget::on_read(QByteArray arr)
{
    qDebug()<<"on_read 构造函数 线程id"<<QThread::currentThread();

    qDebug()<<arr.toHex()<<"---"<<arr;
   ui->plainTextEdit->appendPlainText(arr.toHex());
}
