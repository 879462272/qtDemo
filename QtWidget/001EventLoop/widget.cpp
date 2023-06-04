#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QEvent>
#include <QEventLoop>
#include <QThread>
#include <QTimer>
QEventLoop loop;
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "当前主线程id" << QThread::currentThreadId();
    inInt2();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::inInt2()
{
    m_tt = new Objectmovetothread;
    QThread *thread = new QThread;

    m_tt->moveToThread(thread);

    connect(this, SIGNAL(sig_send()), m_tt, SLOT(slot_while()));
    connect(m_tt, &Objectmovetothread::sig_sendother, this, &Widget::sonfunslot);
    thread->start();
    emit sig_send();


    // 主线程下定时器开启信号槽1s 响应一次.
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, [=]() { qDebug() << "主线程的事件循环" << QThread::currentThreadId(); });
    timer->start(1000);
}

void Widget::sonfunslot()
{
    qDebug() << "当前子线程id:" << QThread::currentThreadId() << "<响应子线程发过来的信号,主线程响应槽>";
}
