#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QIcon>
#include<QAction>
#pragma execution_character_set("utf-8")

//构造函数
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("计算器");

    My_calculator=new Calculator;
    Mycase=begaining;   //开始状态为开始
    result=0;
    myMenuBar=new QMenuBar(this);
    myMenu=new QMenu("菜单",this);
    myMenuBar->addMenu(myMenu);
    QAction *action1=myMenu->addAction("标准");
    QAction *action2=myMenu->addAction("科学");
    connect(action1,&QAction::triggered,
            [=]()
    {
        ui->stackedWidget->setCurrentIndex(0);
        this->on_Button_Clear_clicked();
    });
    connect(action2,&QAction::triggered,
            [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
        this->on_Button_Clear_clicked();
    });

   start();
}


//析构函数
Widget::~Widget()
{
    delete ui;
    delete My_calculator;
}

void Widget::start()
{

    ui->Button_0->setMychar('0');
    connect(ui->Button_0,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_1->setMychar('1');
    connect(ui->Button_1,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_2->setMychar('2');
    connect(ui->Button_2,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_3->setMychar('3');
    connect(ui->Button_3,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_4->setMychar('4');
    connect(ui->Button_4,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_5->setMychar('5');
    connect(ui->Button_5,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_6->setMychar('6');
    connect(ui->Button_6,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_7->setMychar('7');
    connect(ui->Button_7,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_8->setMychar('8');
    connect(ui->Button_8,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_9->setMychar('9');
    connect(ui->Button_9,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_decimal->setMychar('.');
    connect(ui->Button_decimal,&MyButton::mysignal,this,&Widget::IntputChar);

    ui->Button_00->setMychar('0');
    connect(ui->Button_00,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_01->setMychar('1');
    connect(ui->Button_01,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_02->setMychar('2');
    connect(ui->Button_02,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_03->setMychar('3');
    connect(ui->Button_03,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_04->setMychar('4');
    connect(ui->Button_04,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_05->setMychar('5');
    connect(ui->Button_05,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_06->setMychar('6');
    connect(ui->Button_06,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_07->setMychar('7');
    connect(ui->Button_07,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_08->setMychar('8');
    connect(ui->Button_08,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_09->setMychar('9');
    connect(ui->Button_09,&MyButton::mysignal,this,&Widget::IntputChar);
    ui->Button_decimal_2->setMychar('.');
    connect(ui->Button_decimal_2,&MyButton::mysignal,this,&Widget::IntputChar);


    ui->Button_divide->setMychar('/');
    connect(ui->Button_divide,&MyButton::mysignal,this,&Widget::input);
    ui->Button_multiply->setMychar('*');
    connect(ui->Button_multiply,&MyButton::mysignal,this,&Widget::input);
    ui->Button_minus->setMychar('-');
    connect(ui->Button_minus,&MyButton::mysignal,this,&Widget::input);
    ui->Button_plus->setMychar('+');
    connect(ui->Button_plus,&MyButton::mysignal,this,&Widget::input);
    ui->Button_mod->setMychar('%');
    connect(ui->Button_mod,&MyButton::mysignal,this,&Widget::input);
    ui->Button_Left_parenthesis->setMychar('(');
    connect(ui->Button_Left_parenthesis,&MyButton::mysignal,this,&Widget::input);
    ui->Button_Right_parenthesis->setMychar(')');
    connect(ui->Button_Right_parenthesis,&MyButton::mysignal,this,&Widget::input);


    ui->Button_divide_2->setMychar('/');
    connect(ui->Button_divide_2,&MyButton::mysignal,this,&Widget::input);
    ui->Button_multiply_2->setMychar('*');
    connect(ui->Button_multiply_2,&MyButton::mysignal,this,&Widget::input);
    ui->Button_minus_2->setMychar('-');
    connect(ui->Button_minus_2,&MyButton::mysignal,this,&Widget::input);
    ui->Button_plus_2->setMychar('+');
    connect(ui->Button_plus_2,&MyButton::mysignal,this,&Widget::input);
    ui->Button_pow->setMychar('^');
    connect(ui->Button_pow,&MyButton::mysignal,this,&Widget::input);
    ui->Button_mod_2->setMychar('%');
    connect(ui->Button_mod_2,&MyButton::mysignal,this,&Widget::input);

}

//获得表达式最后的一个数字（为单目运算符服务）
double Widget::getnumber()
{
    QString b=Record;
    int i=b.size()-1;

    if(Mycase==begaining) //情况一开始用sin等函数
    {
        //由于用@代表符号代表负号，所以要将@换回‘-’
        if(b.startsWith('@'))
        {
           b.replace(0,1,'-');
        }
        return b.toDouble();
    }

    if(Mycase==ending)  //情况二：一个计算式结束后，用sin等函数
        return result;

    //情况三：在一个表达式中间计算sin
    if(b.back()==')')
    {
        while(b.back()!='(')
        {
            b.chop(1);
            i--;
        }
        b.chop(1);
        i--;
    }
    while(!b.isEmpty()&&b.back()!='+'&&b.back()!='-'&&b!='*'&&b.back()!='/'&&b.back()!='%'&&b.back()!='^')
    {
        b.chop(1);
        i--;
    }

    b=Record.mid(i+1);
    qDebug()<<b;
    if(Record.back()==')')
    {
        My_calculator->postfix(b);
        My_calculator->Run();
        b=My_calculator->getAnswer();
        My_calculator->Clear();
    }

    if(b.startsWith('@'))
    {
       b.replace(0,1,'-');
    }
    qDebug()<<b;
    return b.toDouble();
}

//输入操作符用的函数
void Widget::input(QChar x)
{
    //情况：计算完后继续计算
    if(Mycase==ending)
    {
       out.clear();
       My_calculator->Clear();
       Record.clear();
       ui->label->setText(" ");
       out.append(QString::number(result));
       if(result<0)
       {
           Record.append('@');
       }
       Record.append(QString::number(abs(result)));
    }
    //普通情况
    out.append(x);
    ui->label->setText(out);
    Record.append(x);
    Mycase=ongoing; //设置状态为输入表达式，计算中
    this->ui->Button_equality->setEnabled(true);
     this->ui->Button_equality_2->setEnabled(true);

}

//输入数字用的函数
void Widget::IntputChar(QChar a)
{

    out.append(a);
    ui->label->setText(out);
    Record.append(a);
}



//Π的运用
void Widget::on_Button_pai_clicked()
{
    out.append("3.1415926535");
    ui->label->setText(out);
    Record.append("3.1415926535");
}

//清空
void Widget::on_Button_Clear_clicked()
{
    out.clear();
    My_calculator->Clear();
    Record.clear();
    ui->label->setText(" ");
    Mycase=begaining;
    result=0;
    this->ui->Button_equality->setEnabled(true);
    this->ui->Button_equality_2->setEnabled(true);
}

void Widget::on_Button_Clear_2_clicked()
{
    this->on_Button_Clear_clicked();
}

//清除前一个数
void Widget::on_Button_Clear_entry_clicked()
{

    if(Record.back()==')')
    {
        while(Record.back()!='(')
        {
            Record.chop(1);
        }
        Record.chop(1);
    }
    while(!Record.isEmpty()&&Record.back()!='+'&&Record.back()!='-'&&Record!='*'&&Record.back()!='/'&&Record.back()!='%'&&Record.back()!='^')
    {
        Record.chop(1);
    }


    if(out.back()==')')
    {
        while(out.back()!='(')
        {
            out.chop(1);
        }
        out.chop(1);
    }
    while(!out.isEmpty()&&out.back()!='+'&&out.back()!='-'&&out!='*'&&out.back()!='/'&&out.back()!='%'&&out.back()!='^')
    {
        out.chop(1);
        if(!out.isEmpty())
        {
            if(out.back()=='-'&&!out.at(out.size()-2).isNumber())
            {
                out.chop(1);
            }
        }
    }
   // qDebug()<<out;
    ui->label->setText(out);
}

void Widget::on_Button_Clear_entry_2_clicked()
{
    this->on_Button_Clear_entry_clicked();
}

//清除前面一个字符
void Widget::on_Button_delete_clicked()
{
    out.chop(1);
    Record.chop(1);
    ui->label->setText(out);
}

void Widget::on_Button_delete_2_clicked()
{
    this->on_Button_delete_clicked();
}

//正负号
void Widget::on_Button_plus_minus_clicked()
{
    if(!Record.endsWith('@'))
    {
        out.append('-');
        ui->label->setText(out);
        Record.append('@');
    }
    else
    {
        out.chop(1);
        ui->label->setText(out);
        Record.chop(1);
    }
}

void Widget::on_Button_plus_minus_2_clicked()
{
    this->on_Button_plus_minus_clicked();
}

//科学记数法
void Widget::on_Button_Exp_clicked()
{
    out.append("e+");
    Record.append('e');
    ui->label->setText(out);
}

//等号
void Widget::on_Button_equality_clicked()
{
    //判断输入的表达式是否正确
    if(!My_calculator->FindError(Record))
    {
       out.clear();
       out=My_calculator->getError();
       ui->label->setText(out);
       return;
    }

   //进行运算
   My_calculator->postfix(Record);
   if(!My_calculator->Run())
   {
       out.clear();
       out.append(My_calculator->getError());
       ui->label->setText(out);
       return;
   }
   out.append("=");
   out.append(My_calculator->getAnswer());
   result=My_calculator->getAnswer().toDouble();
   ui->label->setText(out);

   Mycase=ending;

   //按一次后等号不能再按，除非再进行运算
   this->ui->Button_equality->setEnabled(false);

}


void Widget::on_Button_equality_2_clicked()
{
    this->on_Button_equality_clicked();
    this->ui->Button_equality_2->setEnabled(false);
}

//取倒数
void Widget::on_Button_reciprocal_clicked()
{

    double x=getnumber();
    //错误情况
    if(x==0)
    {
        out.append("无效输入");
        ui->label->setText(out);
        return;
    }

    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("1/(%1)=%2").arg(x).arg(1/x);
         result=1/x;
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("1/(%1)").arg(x));
      //负号的交换
      if(x<0)
      {
          Record.append('@');
      }
      Record.append(QString::number(abs(1/x)));
    }
    ui->label->setText(out);
}

//取平方
void Widget::on_Button_square_clicked()
{
    double x=getnumber();
    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("sqr(%1)=%2").arg(x).arg(x*x);
         result=x*x;
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("sqr(%1)").arg(x));
      Record.append(QString::number(x*x));
    }

    ui->label->setText(out);
}

//开根号
void Widget::on_Button_root_clicked()
{

    double x=getnumber();
    if(x<0)
    {
        out.append("无效输入");
        ui->label->setText(out);
        return;
    }

    if(Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("sqrt(%1)=%2").arg(x).arg(sqrt(x));
         result=sqrt(x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("sqrt(%1)").arg(x));
      Record.append(QString::number(sqrt(x)));
    }

    ui->label->setText(out);
}

//sin函数
void Widget::on_Button_sin_clicked()
{

    double  x=getnumber();
    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("sin(%1)=%2").arg(x).arg(sin(x));
         result=sin(x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("sin(%1)").arg(x));
      if(sin(x)<0)
      {
          Record.append('@');
      }
      Record.append(QString::number(abs(sin(x))));
    }

    ui->label->setText(out);
}


//cos函数
void Widget::on_Button_cos_clicked()
{
    double x=getnumber();
    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("cos(%1)=%2").arg(x).arg(cos(x));
         result=cos(x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("cos(%1)").arg(x));
      if(cos(x)<0)
      {
          Record.append('@');
      }
      Record.append(QString::number(abs(cos(x))));
    }

    ui->label->setText(out);

}

//tan函数
void Widget::on_Button_tan_clicked()
{
    double x=getnumber();
    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("tan(%1)=%2").arg(x).arg(tan(x));
         result=tan(x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("tan(%1)").arg(x));
      if(tan(x)<0)
      {
          Record.append('@');
      }
      Record.append(QString::number(abs(tan(x))));
    }
    ui->label->setText(out);
}

//10的次方
void Widget::on_Button_10x_clicked()
{
    double x=getnumber();
    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("10^(%1)=%2").arg(x).arg(pow(10,x));
         result=pow(10,x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("10^(%1)").arg(x));
      Record.append(QString::number(pow(10,x)));
    }

    ui->label->setText(out);
}

//log函数
void Widget::on_Button_log_clicked()
{
   double x=getnumber();
    if(x<=0)
    {
        out.append("无效输入");
        ui->label->setText(out);
        return;
    }

    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("log(%1)=%2").arg(x).arg(log(x));
         result=log(x);
         Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("log(%1)").arg(x));
      if(log(x)<0)
      {
          Record.append('@');
      }
      Record.append(QString::number(abs(log(x))));
    }

    ui->label->setText(out);
}

//阶乘必须是整数
void Widget::on_Button_factorial_clicked()
{
    double x=getnumber();

    if(x<0||Record.back()==')')
    {
        out.append("无效输入");
        ui->label->setText(out);
        return;
    }
    if(!My_calculator->Isint(x))
    {
        out=QString("阶乘必须是整数");
        ui->label->setText(out);
        return;
    }
    int  sum=1;

    for(int i=1;i<=x;i++)
    {
        sum=sum*i;
    }


    if( Mycase==begaining||Mycase==ending)
    {
         out.clear();
         out=QString("fact(%1)=%2").arg(x).arg(sum);
          result=sum;
          Mycase=ending;
    }
    else
    {
      this->on_Button_Clear_entry_clicked();
      out.append(QString("fact(%1)").arg(x));
      Record.append(QString::number(sum));
    }

    ui->label->setText(out);
}


