// Studio21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\CommandPrompt.h"
#include "..\..\\SharedCode\AbstractCommand.h"
#include "..\..\\SharedCode\SimpleFileSystem.h"
#include "..\..\\SharedCode\SimpleFileFactory.h"
#include "..\..\\SharedCode\TouchCommand.h"
#include "..\..\\SharedCode\BasicDisplayVisitor.h"

#include <iostream>

using namespace std;

int main()
{
	AbstractFileSystem* s = new SimpleFileSystem();
	AbstractFileFactory* f = new SimpleFileFactory();
	TouchCommand* t = new TouchCommand(s, f);
	CommandPrompt* cp = new CommandPrompt;
	cp->setFileSystem(s);
	cp->setFileFactory(f);
	cp->addCommand("touch", t);
	cp->run();
	
	string content = "Hello World!";
	vector<char> vcontent(content.begin(), content.end());
	AbstractFile* file = s->openFile("test.txt");
	file->write(vcontent);
	AbstractFileVisitor* vis = new BasicDisplayVisitor();
	file->accept(vis);

}

