#ifndef _MYVECTOR_H
#define _MYVECTOR_H 

#include <iostream>
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

template <class ElemType>
class MyVector 
{
	public:
		MyVector();
		~MyVector();

		int size();
		void add(ElemType s);
		ElemType getAt(int index);
		ElemType removeAt(int index);
		void insertAt(int index, ElemType s);

	private:
		ElemType *arr;
		int numUsed;
		int numAllocated;
		void doubleSpace();
};

#include "myVector.hpp"
#endif  /*_MYVECTOR_H*/
