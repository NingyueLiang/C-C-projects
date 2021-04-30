// Studio18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\SimpleFileSystem.h"
#include "..\..\\SharedCode\SimpleFileFactory.h"

using namespace std;

int main()
{
	AbstractFileSystem* sys = new SimpleFileSystem();
	AbstractFileFactory* fac = new SimpleFileFactory();
	AbstractFile* f = fac->createFile("hello.txt");
	sys->addFile(f->getName(), f);

	string s1 = "Hello, world!";
	vector<char> v1(s1.begin(), s1.end());
	f->write(v1);
	f->read();

	string s2 = " How are you?";
	vector<char> v2(s2.begin(), s2.end());
	f->append(v2);
	f->read();


}
