// Studio19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\ImageFile.h"
#include "..\..\\SharedCode\BasicDisplayVisitor.h"
#include "..\..\\SharedCode\MetadataDisplayVisitor.h"

#include <iostream>


using namespace std;

int main()
{
	ImageFile* i = new ImageFile("test_img");
	vector<char> pic = { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' };
	i->write(pic);
	BasicDisplayVisitor* v = new BasicDisplayVisitor();
	i->accept(v);
	MetadataDisplayVisitor* m = new MetadataDisplayVisitor();
	i->accept(m);


}
