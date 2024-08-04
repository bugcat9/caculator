#include "calculator.h"
#include<QString>
#include<QDebug>
#include<string>
#include<QByteArray>
#include<QVector>
#include<qmath.h>
#pragma execution_character_set("utf-8")

Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}

bool Calculator::Run()
{
    //计算结果
    double x=0,y=0,z=0;
    QString a;
    ListNode<QChar> *cur=expression.getfist()->next;
    while(cur->data!='#')
    {

        if(cur->data.isNumber()||cur->data=='.'||cur->data=='@')
        {
            if(cur->data=='@')
            {
                cur->data='-';
            }
            a.append(cur->data);
        }
        else if (cur->data==' ')
        {
            numbers.Push(a.toDouble());
            a.clear();
            //cur=cur->next;

        }
        else
        {
            numbers.Pop(x);
            numbers.Pop(y);
            switch (cur->data.toLatin1())
            {
            case '+':z=x+y;break;
            case '-':z=y-x; break;
            case '*':z=x*y;break;
            case '/':
                if(x==0.0)
                {

                   error=QString("除数不能为0");
                   return false;
                }
                z=y/x; break;
            case '^':z=pow(y,x);break;
            case 'e':z=y*pow(10,x);break;
            case '%':
                if(Isint(x)&&Isint(y))
                     z=int(y)%int(x);
                else
                {
                    error=QString("取余必须都是整数");
                    return false;
                }
                break;
            }
            numbers.Push(z);
        }
         cur=cur->next;

  }

     numbers.Pop(z);
     answer=QString::number(z);
     return true;
    //qDebug()<<z;
}

void Calculator::Clear()
{
    numbers.makeEmpty();
    expression.makeEpmty();
    answer.clear();
    error.clear();

}

//转化为后缀表达式
void Calculator::postfix(QString e)
{
        qDebug()<<e;
        //转化为后缀表达式
        stack<QChar>s2;
        QChar ch = '#', ch1;
        s2.Push('#');
        QString a;
        for (int i = 0; i <e.size(); i++)
        {
            ch = e[i];
            if (ch.isNumber()||ch=='.'||ch=='@')
            {

                expression.push(ch);
                a.append(ch);
                //qDebug()<<a;
                continue;
            }
            while (!s2.IsEmpty()&& ch!= '#')
            {
                if(!a.isEmpty())
                {

                    a.clear();
                    expression.push(' ');//添加空格用以区分两个操作数
                }
                s2.getTop(ch1);
                if (icp(ch)>isp(ch1))
                {
                    s2.Push(ch);
                    break;
                }
                else if (icp(ch) == isp(ch1))
                {

                    s2.Pop(ch1);
                    if(ch1=='(')
                        break;
                }
                else if (icp(ch)<isp(ch1))
                {

                    s2.Pop(ch1);
                    expression.push(ch1);
                }
            }
        }
        //防止最后一个操作数没有插入空格
        if(!a.isEmpty())
        {
            a.clear();
            expression.push(' ');
        }

        while (!s2.IsEmpty())
         {
                s2.Pop(ch1);
                expression.push(ch1);
         }

}

//计算运算符c的栈外优先级
int Calculator::icp(QChar c)
{
    int priority;
        switch (c.toLatin1())
        {
        case '(':priority = 7; break;
        case '+':
        case '-':priority = 2; break;
        case '%':
        case '*':
        case 'e':
        case '/':priority = 4; break;
        case '#':priority = 0; break;
        case ')':priority = 1; break;
        case '^':priority = 5; break;
        }
        return priority;
}

int Calculator::isp(QChar c)
{
    //计算运算符c的栈内优先级
        int priority;
        switch (c.toLatin1())
        {
        case '(':priority = 1; break;
        case '+':
        case '-':priority = 3; break;
        case '%':
        case '*':
        case 'e':
        case '/':priority = 5; break;
        case '#':priority = 0; break;
        case ')':priority = 7; break;
        case '^':priority = 6; break;
        }
        return priority;
}

bool Calculator::FindError(QString e)
{
   qDebug()<<e;
   if(!MatchedPairs(e))
   {

       error=QString("括号不匹配");
       return false;
   }

   for(int i=0;i<e.size();i++)
   {
       //如果不是数据即是运算符，判断运算符前后是否是数字
       if(!e[i].isNumber()&&e[i]!='('&&e[i]!=')'&&e[i]!='@')
       {
           if(i==0)
           {
               error=QString("错误输入");
               return false;
           }
           else if(!e[i-1].isNumber()&&e[i-1]!='('&&e[i-1]!=')'&&e[i-1]!='@')
           {
               error=QString("错误输入");
               return false;
           }
           else if(!e[i+1].isNumber()&&e[i+1]!='('&&e[i+1]!=')'&&e[i+1]!='@')
           {
               error=QString("错误输入");
                return false;
           }

       }
   }

   return true;
}

//括号匹配
bool Calculator::MatchedPairs(QString e)
{
    stack<QChar> s;
    QChar x;
    for(int i=0;i<e.size();i++)
    {
        if(e[i]=='(')
            s.Push(e[i]);
        else if(e[i]==')')
        {
            if(!s.Pop(x))
                return false;
        }
    }

    if(!s.IsEmpty())
        return false;
    return true;
}

QString Calculator::getAnswer()
{
    return answer;
}

QString Calculator::getError()
{
    return error;
}

//判断输入的是否是整数
bool Calculator::Isint(double x)
{
    long int y=(long int) x;
        //if ((x-y)!=0)//这段代码可能会丢失精度
       if((x-y)!=0)
           return false;
        return true;
}

