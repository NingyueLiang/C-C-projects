// Studio17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\ImageFile.h"
#include "..\..\\SharedCode\SimpleFileSystem.h"
#include <iostream>

using namespace std;


int main()
{
	ImageFile* i = new ImageFile("test_img");
	vector<char> pic = { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' };
	i->write(pic);
	i->append(pic);
	i->read();
	cout << i->getName() << endl;
	cout << i->getSize() << endl;

	SimpleFileSystem* s = new SimpleFileSystem();
	s->addFile("1.img", i);
	s->createFile("2.txt");
	s->closeFile(s->openFile("1.img"));
	s->deleteFile("2.txt");

	
}

