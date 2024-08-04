#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QChar>

/*
 * 自定义的button类，继承于QPushButton，
 * 其中数据成员mychar记录自己的数据
 * 函数成员mousePressEvent功能为按下后发射信号mysignal
 * 信号mysignal，主要为了传输字符串
 */
class MyButton : public QPushButton
{
    Q_OBJECT
public:

    explicit MyButton(QWidget *parent = nullptr);
    MyButton(QChar a,QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);
    void setMychar(QChar a);

    QChar mychar;   //
signals:
    void mysignal(QChar a);
public slots:
};

#endif // MYBUTTON_H
