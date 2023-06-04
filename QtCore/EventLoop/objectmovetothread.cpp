#include "objectmovetothread.h"
#include <QDebug>
#include <QEventLoop>
#include <QThread>
#include <QTimer>
Objectmovetothread::Objectmovetothread(QObject *parent)
{

    // 构造时候还在主线程中，movetothread之后才在子线程之中。
    qDebug() << "构造时子线程id:当前线程Id:<Objectmovetothread> " << QThread::currentThreadId();
    connect(this, SIGNAL(sig_sendthe()), this, SLOT(slot_getfunthe()));

    // 主事件循环创建信号，
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Objectmovetothread::slot_getfunother);
    timer->start(1000);
}

void Objectmovetothread::slot_getfunother()
{
    qDebug() << "响应定时器 ,当前子线程Id:<slot_getfunother>" << QThread::currentThreadId();
}

void Objectmovetothread::slot_getfunthe()
{
    QEventLoop loop;
    qDebug() << "当前线程Id:<slot_getfunthe>" << QThread::currentThreadId();

    // 这个屏蔽了的话下列的while循环会得不到执行，因为该子事件循环会阻塞运行到后续的代码，即函数返回不出去。
    // 这里还是会接管主事件循环中的定时器，即不会阻塞信号队列，上面的定时器还是会执行。这里是否可以理解成让出了时间片.
    //  QTimer::singleShot(2, &loop, SLOT(quit()));
    loop.exec();
}

void Objectmovetothread::slot_while()
{
    qDebug() << "当前线程Id:<slot_while> " << QThread::currentThreadId();
    int i = 0;
    while (m_falgs) {
        i++;
        qDebug() << "RUN 循环 " << i;

        emit sig_sendthe();

        // emit sig_sendother();
    }
}
