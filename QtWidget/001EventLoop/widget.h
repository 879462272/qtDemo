#ifndef WIDGET_H
#define WIDGET_H

#include "objectmovetothread.h"

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void sig_send();
private slots:


    void inInt2();

    void sonfunslot();


private:
    Ui::Widget *ui;


    Objectmovetothread *m_tt;
};
#endif  // WIDGET_H
