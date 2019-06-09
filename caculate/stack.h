#ifndef STACK_H
#define STACK_H

#include<iostream>

//结点
template<class T>
struct ListNode
{
    T data;
    ListNode *next;
    ListNode(T data=0,ListNode *next=NULL)
    {
        this->data=data;
        this->next=next;
    }
};

//栈模板
template<class T>
class stack
{
public:
    stack();                       //构造函数
    ~stack();                     //析构函数
    void Push(T x);              //入栈
    bool Pop(T &x);             //出栈
    bool getTop(T &x)const;     //获得栈顶元素
    bool IsEmpty()const;        //判空
    int getSize()const;         //获得栈的大小
    void makeEmpty();           //清空

private:
    ListNode<T> *top;           //栈的头指针
    int size;                   //栈的大小
};


template<class T>
stack<T>::stack()
{
    top=NULL;
}

template<class T>
stack<T>::~stack()
{
    ListNode<T> *p;
    while(top!=NULL)
    {
        p=top;
        top=top->next;
        delete p;
    }

}

template<class T>
void stack<T>::Push(T x)
{
    top=new ListNode<T>(x,top);
    size++;
}

template<class T>
bool stack<T>::Pop(T &x)
{
    if(IsEmpty()==true)
        return false;
    ListNode<T> *p=top;
    top=top->next;
    x=p->data;
    delete p;
    size--;
    return true;

}

template<class T>
bool stack<T>::getTop(T &x) const
{
    if(IsEmpty())
        return false;
    x=top->data;
    return true;
}

template<class T>
bool stack<T>::IsEmpty() const
{
    if(top!=NULL)
        return false;
    return true;

}

template<class T>
int stack<T>::getSize() const
{
    return size;
}

template<class T>
void stack<T>::makeEmpty()
{
    ListNode<T> *p;
    while(top!=NULL)
    {
        p=top;
        top=top->next;
        delete p;
    }
    top=NULL;
}

#endif // STACK_H
