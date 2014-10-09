#ifndef ARRAY_H__
#define ARRAY_H__ 

#include <iostream>

class Array {
	friend std::ostream & operator<< (std::ostream &os, const Array &a);
	friend const Array & operator+ (const Array &a1, const Array &a2);

	friend bool operator< (const Array &a1, const Array &a2);
	friend bool operator<= (const Array &a1, const Array &a2);
	friend bool operator>= (const Array &a1, const Array &a2);
	friend bool operator> (const Array &a1, const Array &a2);
	friend bool operator== (const Array &a1, const Array &a2);
	friend bool operator!= (const Array &a1, const Array &a2);

public:
	Array(size_t len = 1, int data = 0);
	~Array();

	Array(const Array &a);
	Array & operator= (const Array &a);
	Array & operator+= (const Array &a);

	int & operator[] (size_t index) { return *(arr_+ index); }
	const int & operator[] (size_t index) const { return *(arr_ + index); }

	operator int *() { return arr_; }
	size_t size() const { return len_; }
private:
	size_t len_;
	int *arr_;
};

#endif  /*ARRAY_H__*/
