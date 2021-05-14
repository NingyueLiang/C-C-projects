#pragma once
//Lab5 FL & PJ: this file defines remove command
#include "AbstractCommand.h"

class RemoveCommand : public AbstractCommand {
public:
	RemoveCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~RemoveCommand() = default;
private:
	AbstractFileSystem* sys;
}; 

