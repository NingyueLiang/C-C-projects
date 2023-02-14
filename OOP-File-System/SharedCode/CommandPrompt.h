#pragma once
//Lab 5 FL & JP This file defines command prompt class
#include <string>
#include <map>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class CommandPrompt {
public:
	CommandPrompt();
	~CommandPrompt();
	void setFileSystem(AbstractFileSystem*);
	void setFileFactory(AbstractFileFactory*);
	int addCommand(std::string, AbstractCommand*);
	int run();
protected:
	void listCommands(); 
	std::string prompt();
private:
	std::map<std::string, AbstractCommand*> commands;
	AbstractFileSystem* system;
	AbstractFileFactory* factory;
};

enum prompt {prompt_success = 0, prompt_exist = 63, user_quit = 64, prompt_fail = 65, prompt_invalid = 66};