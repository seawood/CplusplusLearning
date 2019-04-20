#include <iostream>
#include <map>
#include "StrVec.h"
using namespace std;

int main() {
	StrVec s1;
	s1.push_back("hello");
	cout << *s1.begin() << endl;
	StrVec s2 = s1;
	cout << *s2.begin() << endl;
	StrVec s3;
	s3 = s2;
	cout << *s3.begin() << endl;
	StrVec s4(move(s3));
	cout << "s3 capacity:" << s3.capacity() << endl;
	cout << *s4.begin() << endl;
	StrVec s5;
	s5 = StrVec();
	system("PAUSE");
	return 0;
}

