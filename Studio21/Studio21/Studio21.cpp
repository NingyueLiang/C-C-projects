// Studio21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\CommandPrompt.h"
#include "..\..\\SharedCode\AbstractCommand.h"
#include "..\..\\SharedCode\SimpleFileSystem.h"
#include "..\..\\SharedCode\SimpleFileFactory.h"
#include "..\..\\SharedCode\TouchCommand.h"

int main()
{
	AbstractFileSystem* s = new SimpleFileSystem();
	AbstractFileFactory* f = new SimpleFileFactory();
	TouchCommand* t = new TouchCommand(s, f);
	CommandPrompt* cp = new CommandPrompt;
	cp->setFileSystem(s);
	cp->setFileFactory(f);
	cp->addCommand("touch", t);
	cp->addCommand("touch2", t);
	cp->run();
}

