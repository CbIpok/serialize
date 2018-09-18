// test_serialize.cpp
#include <fstream>
#include <iostream>
#include "serialize.h"

using namespace std;

int main()
{
	ofstream ofs("test.ser", ofstream::out | ofstream::binary);

	char hello[7] = "hello!";
	int boo[3] = { 1, 2, 3 };

	serialize(hello, ofs);
	serialize(boo, ofs);

	char hello2[7];
	int boo2[3];

	ofs.close();

	ifstream ifs("test.ser", ifstream::in | ofstream::binary);
	ifs >> noskipws;

	deserialize(hello2, ifs);
	deserialize(boo2, ifs);

	if (equal(hello, hello + 7, hello2))
		cout << "Hello Ok" << endl;

	if (equal(boo, boo + 3, boo2))
		cout << "Boo OK!" << endl;

	return 0;
}