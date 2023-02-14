// Studio20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\ImageFile.h"
#include "..\..\\SharedCode\BasicDisplayVisitor.h"
#include "..\..\\SharedCode\MetadataDisplayVisitor.h"
#include "..\..\\SharedCode\PasswordProxy.h"

#include <iostream>


using namespace std;
int main()
{
	AbstractFile* i = new ImageFile("test_img");
	vector<char> pic = { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' };
	i->write(pic);
	PasswordProxy* pi = new PasswordProxy(i, "studio");
	BasicDisplayVisitor* v = new BasicDisplayVisitor();
	pi->read();
	pi->accept(v);
	MetadataDisplayVisitor* m = new MetadataDisplayVisitor();
	pi->accept(m);
	pic = { 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' };
	pi->write(pic);
	pi->accept(v);
	return 0;
}

