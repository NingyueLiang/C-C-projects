#pragma once
//Lab5 Frank Liang & Pan Joe: This file declare an abstract interfere for command
#include <string>
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class AbstractCommand {
public:
	virtual ~AbstractCommand() = default;
	virtual int execute(std::string) = 0;
	virtual void displayInfo() = 0;
};