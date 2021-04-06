// Studio16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\TextFile.h"
#include <iostream>

using namespace std;

int main()
{
	TextFile f("test");
	string s1 = "Hello, world!";
	vector<char> v1(s1.begin(), s1.end());
	f.write(v1);
	f.read();

	string s2 = "Nice to meet you!";
	vector<char> v2(s2.begin(), s2.end());
	f.write(v2);
	f.read();
	
	string s3 = " How are you?";
	vector<char> v3(s3.begin(), s3.end());
	f.append(v3);
	f.read();

	cout << "File name is " << f.getName() << endl;
	cout << "File size is " << f.getSize() << endl;
}

