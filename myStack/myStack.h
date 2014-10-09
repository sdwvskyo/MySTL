#ifndef _MY_STACK
#define _MY_STACK 

#include <iostream>

template <class Elemtype>
class MyStack
{
public:
	MyStack();
	~MyStack();
	
	int size();
	void push(Elemtype e);
	Elemtype pop();
private:
	vector<Elemtype> elem;
}
#include "myStack.hpp"
#endif  /*_MY_STACK*/
