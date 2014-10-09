/*
 * 使用C++11新特性：右值引用
 * 右值引用可以实现转移语义
 * 在复制构造函数和使用赋值运算符时可以节省拷贝的时间
 *
 */

#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
	String();
	String(const char *s);
	String(const String &s);
	String(String &&s);	//转移语义
	~String();
	
	String &operator(const String &s);
	String &operator(String &&s);

	friend ostream &operator<<(ostream &os, const String &s)
	{
		return os << s.data_;
	}

private:
	char *data_;	
};

String::String()
	: data_(new char[1])
{
	*data_ = 0;
}

String::String(const char *s)
	: data_(new char[strlen(s) + 1])
{
	::strcpy(data_, s);
}

String::String(const String &s)
	: data_(new char[strlen[s.data_] + 1])
{
	::strcpy(data_, s.data_);
}

String::String(String &&s)
	: data_(s.data_)
{
	s.data_ = NULL;
}

String &String::operator=(const String &s)
{
	if (this != &s) {
		delete [] data_;
		data_ = new char[strlen(s.data_) + 1];
		::strcpy(data_, s.data_);
	}
}

String &String::operator=(String &&s)
{
	if (this != &s) {
		delete data_;
		data_ = s.data_;
		s.data_ = NULL;
	}
}
