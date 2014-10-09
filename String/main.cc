#include "String.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, const char *argv[])
{
	String s = "Hello";
	s.debug();

	String s2(s);
	cout << s2 << endl;
	String s3 = s2;
	cout << s3 << endl;

	s3 = "world";
	cout << s + s3 + s2 << endl;
	cout << "s " << s << endl;
	cout << "s2 " << s2 << endl;
	s += s2;
	cout << s + s << endl;
	
	String t1 = "foobal";
	String t2 = "hello";

	assert(t1 < t2);
	assert(t2 > t1);
	assert(t1 <= t2);
	assert(t2 >= t1);
	assert(t1 != t2);
	assert(!(t1 == t2));

	s = "hello";
	cout << s[3] << endl;
	s[3] = 'A';
	cout << s << endl;

	return 0;
}
