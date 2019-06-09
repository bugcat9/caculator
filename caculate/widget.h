#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include"calculator.h"
#include"math.h"
#include<QMenuBar>
#include<QMenu>
#include"mybutton.h"
namespace Ui {
class Widget;
}

//枚举类型，记录计算时的状态
enum Calculationcase
{
    ongoing,ending,begaining
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void IntputChar(QChar a);     //输入数字
    void input(QChar x);          //  输入操作符

    double getnumber();           //正对单目运算符（如：sin）,获得该输入sin中的函数

    void start();                 //开始函数，将一些信号、槽函数连接

private slots:


    void on_Button_Clear_clicked();

    void on_Button_Clear_entry_clicked();

    void on_Button_delete_clicked();

    void on_Button_equality_clicked();

    void on_Button_plus_minus_clicked();

    void on_Button_reciprocal_clicked();

    void on_Button_root_clicked();

    void on_Button_square_clicked();

    void on_Button_sin_clicked();

    void on_Button_cos_clicked();

    void on_Button_tan_clicked();

    void on_Button_10x_clicked();

    void on_Button_log_clicked();

    void on_Button_factorial_clicked();

    void on_Button_Exp_clicked();

    void on_Button_pai_clicked();

    void on_Button_plus_minus_2_clicked();

    void on_Button_Clear_entry_2_clicked();

    void on_Button_Clear_2_clicked();

    void on_Button_delete_2_clicked();

    void on_Button_equality_2_clicked();

private:
    Ui::Widget *ui;
    QString out;                    //屏幕的输出
    QString Record;                 //记录表达式
    Calculationcase Mycase;         //运算时的状态
    Calculator *My_calculator;      //定义自己的计算器
    double result;                  //保存结果
    QMenuBar *myMenuBar;            //菜单栏
    QMenu *myMenu;                  //菜单
};

#endif // WIDGET_H
