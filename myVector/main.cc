#include <iostream>
#include <string>
#include "myVector.h"

using namespace std;

int main(int argc, const char *argv[])
{
	MyVector<int> vec;
	vec.add(1);
	vec.add(20);
	vec.add(99);
	cout << vec.size() << endl;
	for (int i = 0; i < vec.size(); ++i)
		cout << vec.getAt(i) << endl;
	return 0;
}
