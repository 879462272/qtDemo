#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"contralseriesport.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



signals:
    int32_t open(QString PortName,int BaudRate, int DataBits, int Parity, int StopBits);

    int32_t writredata(bool hex,QString str);

    int close();
    int exit();
private slots:
    void on_open_clicked();
    void on_send_clicked();
    void on_read(QByteArray arr);
private:
    void inIntSlots();

private:
    Ui::Widget *ui;
    WorkSeriesPort *m_doWork;
};
#endif // WIDGET_H
