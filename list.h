#ifndef LIST_H
#define LIST_H
#include"stack.h"

template<class T>
class List
{
public:
    List(); //构造函数
    ~List(); //析构函数
    void push(T x); //将x插入尾部
    int getsize();  //获得链表的大小
    ListNode<T> * getfist();    //得到头节点
    void makeEpmty();   //清空
private:
    ListNode<T> *first; //头节点无实际意义
    ListNode<T> *last;  //尾指针
    int size;           //链表的大小
};

//构造函数
template<class T>
List<T>::List()
{
    first=new ListNode<T>;
    size=0;
    last=first;
}

//析构函数
template<class T>
List<T>::~List()
{
    ListNode<T> *p=first->next;
    while(first->next!=NULL)
    {
        p=first->next;
        first->next=p->next;
        delete p;
    }
    delete first;
    last=NULL;
    size=0;
}

//插入函数
template<class T>
void List<T>::push(T x)
{
    ListNode<T> *newNode=new ListNode<T>(x);
    last->next=newNode;
    last=newNode;
    size++;
}

//获得链表的大小函数
template<class T>
int List<T>::getsize()
{
    return size;
}

//获得头节点
template<class T>
ListNode<T> *List<T>::getfist()
{
    return first;
}

//将链表清空
template<class T>
void List<T>::makeEpmty()
{
    ListNode<T> *p=first->next;
    while(first->next!=NULL)
    {
        p=first->next;
        first->next=p->next;
        delete p;
    }
    last=first;
    size=0;
}











#endif // LIST_H
