#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<QString>
#include"stack.h"
#include<QChar>
#include"list.h"
class Calculator
{
public:
    Calculator();   //计算器的构造函数
    ~Calculator();  //析构函数
    bool Run();     //用于转化为后缀表达式后的计算
    void Clear();   //清空表达式
    void postfix(QString e);        //将中缀表达式转化为后缀表达式
    int icp(QChar c);               //判断运算符c的栈外优先级
    int isp(QChar c);               //判断运算符c的栈内优先级
    bool FindError(QString e);      //判断表达式的输入是否合法
    bool MatchedPairs(QString e);   //判断括号是否匹配
    QString getAnswer();            //获得最后的答案
    QString getError();             //获得错误信息
    bool Isint(double x);           //判断输入的是否是整数
private:
    stack<double>numbers;            //栈用于存放计算过程的数字
    List<QChar>expression;           //用于存储后缀表达式（其实用数组也能达到相同效果）
    QString answer;                  //最后的答案
    QString error;                   //表达式的错误

};

#endif // CALCULATOR_H
