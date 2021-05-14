// Lab5.cpp : Frank Liang & Joe Pan This file contains the 'main' function. Program execution begins and ends there.
//
#include "../../SharedCode/TextFile.h"
#include "../../SharedCode/ImageFile.h"
#include "../..//SharedCode/SimpleFileFactory.h"
#include "../../SharedCode/SimpleFileSystem.h"
#include "../../SharedCode/BasicDisplayVisitor.h"
#include "../../SharedCode/MetadataDisplayVisitor.h"
#include "../../SharedCode/TouchCommand.h"
#include "../../SharedCode/CommandPrompt.h"
#include "../../SharedCode/DisplayCommand.h"
#include "../../SharedCode/LSCommand.h"
#include "../../SharedCode/RemoveCommand.h"
#include "../../SharedCode/CatCommand.h"
#include "../../SharedCode/CopyCommand.h"

using namespace std;

int main()
{
	AbstractFileFactory* fac = new SimpleFileFactory();
	AbstractFileSystem* sys = new SimpleFileSystem();
	CommandPrompt* cmd = new CommandPrompt();

	cmd->setFileFactory(fac);
	cmd->setFileSystem(sys);

	TouchCommand* touchC = new TouchCommand(sys, fac);
	LSCommand* LS = new LSCommand(sys);
	RemoveCommand* rmv = new RemoveCommand(sys);
	CatCommand* ct = new CatCommand(sys);
	DisplayCommand* dp = new DisplayCommand(sys);
	CopyCommand* copy = new CopyCommand(sys);

	cmd->addCommand("touch", touchC);
	cmd->addCommand("ls", LS);
	cmd->addCommand("rm", rmv);
	cmd->addCommand("cat", ct);
	cmd->addCommand("ds", dp);
	cmd->addCommand("cp", copy);

	cmd->run();
}


