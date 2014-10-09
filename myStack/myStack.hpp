#ifndef MYSTACK_HPP_
#define MYSTACK_HPP_ 

#include "MyStack.h"

template <typename Elemtype>
MyStack<Elemtype>::MyStack()
{

}

template <typename Elemtype>
MyStack<Elemtype>::~MyStack()
{

}

template <typename Elemtype>
int MyStack<Elemtype>::size()
{
	return elem.size();
}

template <typename Elemtype>
void MyStack<Elemtype>::push(Elemtype e)
{
	elem.add(e);
}

template <typename Elemtype>
Elemtype MyStack<Elemtype>::pop()
{
	Elemtype top = elem[elem.size() - 1];
	elem.removeAt(elem.size() - 1);
	return top;
}

#endif  /*MYSTACK_HPP_*/
