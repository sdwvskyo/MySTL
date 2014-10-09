#ifndef STRING_H__
#define STRING_H__ 

#include <iostream>
#include <string.h>

class String {
	friend std::ostream & operator<<(std::ostream &os, const String &s);
	friend std::istream & operator>>(std::istream &is, String &s);

	friend const String operator+ (const String &s1, const String &s2);
	friend const String operator+ (const String &s1, const char *str);
	friend const String operator+ (const char *str, const String &s2);

	friend bool operator< (const String &s1, const String &s2);
	friend bool operator<= (const String &s1, const String &s2);
	friend bool operator> (const String &s1, const String &s2);
	friend bool operator>= (const String &s1, const String &s2);
	friend bool operator!= (const String &s1, const String &s2);
	friend bool operator== (const String &s1, const String &s2);

public:
	String();
	String(const char *str);
	String(const String &s);
	~String();

	String & operator= (const char *str);
	String & operator= (const String &s);
	String & operator+= (const char *str);
	String & operator+= (const String &s);

	char & operator[] (size_t index) { return str_[index]; }
	const char & operator[] (size_t index) const { return str_[index]; }

	const char * c_str() { return str_; }
	size_t size() const { return strlen(str_); }

	operator char*() const { return str_; }

	void swap(String &other);
	void debug() const;

private:
	char *str_;
};

#endif  /*STRING_H__*/
