#include "mybutton.h"
#include<QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
    mychar='0';
}

MyButton::MyButton(QChar a, QWidget *parent):mychar(a),QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *)
{
    emit mysignal(mychar);
  //   qDebug()<<mychar;
}

void MyButton::setMychar(QChar a)
{
  mychar=a;
  qDebug()<<a;
}
