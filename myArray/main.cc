#include "Array.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, const char *argv[])
{
	Array a1(10, 99);
	cout << a1 << endl;

	Array a2(5);
	cout << a2 << endl;

	cout << a1 + a2 << endl;

	assert(a1 > a2);

	Array a3(a1);
	assert(a1 == a3);
	assert(!(a1 != a3));
	return 0;
}
