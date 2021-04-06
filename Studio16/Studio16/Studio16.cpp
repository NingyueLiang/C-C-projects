// Studio16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\TextFile.h"
#include <iostream>

using namespace std;


int main()
{
	TextFile f("test");
	std::string s1 = "Hello, world!";
	std::vector<char> v1(s1.begin(), s1.end());
	f.write(v1);
	f.read();

	std::string s2 = "Hello, world!";
	std::vector<char> v2(s2.begin(), s2.end());
	f.write(v2);
	f.read();
}

