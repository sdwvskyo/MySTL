#include "Array.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Array::Array(size_t len, int data) 
	: len_(len), arr_(new int[len])
{  
	for (size_t i = 0; i < len; ++i) {
		arr_[i] = data;
	}
}

Array::~Array()
{
	delete [] arr_;
}

Array::Array(const Array &a) 
	: len_(a.size()), arr_(new int[a.size()])
{
	for (size_t i = 0; i < len_; ++i) {
		arr_[i] = a[i];
	}
}

Array & Array::operator= (const Array &a)
{
	len_ = a.size();
	if (arr_ != a.arr_) {
		delete [] arr_;
		arr_ = new int[len_];
		for(size_t i = 0; i < len_; ++i) {
			arr_[i] = a.arr_[i];
		}
	}
	return *this;
}

Array & Array::operator+= (const Array &a)
{
	size_t len = len_ + a.size();
	int *tmp = new int[len];
	size_t i = 0;
	for( ; i < len_; ++i) {
		tmp[i] = arr_[i];
	}
	size_t j = 0;
	for( ; i < len; ++i, ++j) {
		tmp[i] = a.arr_[j];
	}
	delete [] arr_;
	len_ = len;
	arr_ = tmp;
	return *this;
}


std::ostream & operator<< (std::ostream &os, const Array &a)
{
	size_t i = 0;
	for(i = 0; i < a.size() - 1; ++i) {
		os << a.arr_[i] <<  ", ";
	}
	os << a.arr_[i];
	return os; 
}

const Array & operator+ (const Array &a1, const Array &a2)
{
	Array *tmp = new Array(a1);
	*tmp += a2;
	return *tmp;
}

bool operator< (const Array &a1, const Array &a2)
{
	if (a1.size() != a2.size())	{
		return a1.size() < a2.size();
	} else {
		for(size_t i = 0; i < a1.size(); ++i) {
			if (a1[i] != a2[i]) {
				return a1[i] < a2[i];
			}
		}
	}
	return false;
}

bool operator<= (const Array &a1, const Array &a2)
{
	return !(a1 > a2);
}

bool operator>= (const Array &a1, const Array &a2)
{
	return !(a1 < a2);
}

bool operator> (const Array &a1, const Array &a2)
{
	return a2 < a1;
}

bool operator== (const Array &a1, const Array &a2)
{
	return (a1 >= a2) && (a1 <= a2);
}

bool operator!= (const Array &a1, const Array &a2)
{
	return !(a1 == a2);
}
