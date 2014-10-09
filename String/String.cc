#include "String.h"
#include <iostream>
#include <string.h>
#include <stdexcept>

using namespace std;

String::String() 
	: str_(new char[1])
{
	str_[0]= 0;
}

String::~String()
{
	delete [] str_;
}

String::String(const char *str) 
	: str_(new char[strlen(str) + 1])
{
	::strcpy(str_, str);
}

String::String(const String &s)
	: str_(new char[s.size() + 1])
{
	::strcpy(str_, s.str_);
}

String & String::operator= (const char *str)
{
	if (str_ != str) {
		delete [] str_;
		str_ = new char[strlen(str) + 1];
		if (!str)
			throw runtime_error("malloc memory error in operator=");
		::strcpy(str_, str);
	}
	return *this;
}

String & String::operator= (const String &s)
{
	if (*this != s) {
		delete [] str_;
		str_ = new char[s.size() + 1];
		if (!str_)
			throw runtime_error("malloc memory error in operator=");
		::strcpy(str_, s.str_);
	}
	return *this;
}

String & String::operator+= (const char *str)
{
	*this = *this + str;
	return *this;
}

String & String::operator+= (const String &s)
{
	*this = *this + s;
	return *this;
}

void String::swap(String &other)
{
	::swap(str_, other.str_);
}

void String::debug() const
{
	cout << str_ << endl;
}

std::ostream & operator<< (std::ostream &os, const String &s)
{
	return os << s.str_;
}

std::istream & operator>> (std::istream &is, String &s)
{
	char tmp[1024];
	if (is >> tmp)
		s = tmp;
	return is;
}

const String operator+ (const String &s1, const String &s2)
{
	char *str = new char[s1.size() + s2.size() + 1];
	str[0] = 0;
	::strcat(str, s1.str_);
	::strcat(str, s2.str_);
	String tmp(str);
	delete [] str;
	return tmp;
}

const String operator+ (const String &s1, const char *str)
{
	return s1 + String(str);
}
const String operator+ (const char *str, const String &s2)
{
	return String(str) + s2;
}

bool operator< (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) < 0;
}

bool operator<= (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) <= 0;
}

bool operator> (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) > 0;
}

bool operator>= (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) >= 0;
}

bool operator!= (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) != 0;
}

bool operator== (const String &s1, const String &s2)
{
	return ::strcmp(s1.str_, s2.str_) == 0;
}

