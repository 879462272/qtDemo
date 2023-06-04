#ifndef OBJECTMOVETOTHREAD_H
#define OBJECTMOVETOTHREAD_H

#include <QObject>

class Objectmovetothread : public QObject
{
    Q_OBJECT
public:
    Objectmovetothread(QObject *parent = nullptr);


signals:
    void sig_sendthe();
    void sig_sendother();
public slots:
    void slot_getfunother();
    void slot_getfunthe();
    void slot_while();

public:
private:
    int nUm;
    bool m_falgs;
};

#endif  // OBJECTMOVETOTHREAD_H
