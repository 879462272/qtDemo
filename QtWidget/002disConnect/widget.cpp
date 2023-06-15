#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QUrl>
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString path = QCoreApplication::applicationDirPath() + QString("/../1.txt");
    qDebug() << path;
    QDir temDir("./1.txt");
    QString str = temDir.absolutePath();
    qDebug() << "相对路径转绝对路径 " << str;
    QUrl q = QUrl::fromLocalFile(str);
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    qDebug() << in.readAll();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    qDebug() << "武汉";
}

void Widget::on_pushButton_2_clicked()
{
    qDebug() << "广东";
}

void Widget::on_pushButton_3_clicked()
{
    qDebug() << "非洲";
}

void Widget::on_pushButton_4_clicked()
{
    // qDebug() << ui->pushButton->disconnect();
    qDebug() << QObject::disconnect(ui->pushButton, 0, this, 0);
}

void Widget::on_pushButton_5_clicked()
{

    qDebug() << ui->pushButton_2->disconnect();
}

void Widget::on_pushButton_6_clicked()
{

    qDebug() << ui->pushButton_3->disconnect();
}

// 断开路径.
void Widget::on_pushButton_7_clicked()
{
    disconnect(ui->pushButton, SIGNAL(clicked()), 0, 0);
    disconnect(ui->pushButton_2, SIGNAL(clicked()), 0, 0);
    disconnect(ui->pushButton_3, SIGNAL(clicked()), 0, 0);
}


// 连接路径.
void Widget::on_pushButton_8_clicked()
{

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
}
