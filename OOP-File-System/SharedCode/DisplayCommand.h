#pragma once
//Lab5 FL & PJ: this file defines ds command
#include "AbstractCommand.h"

class DisplayCommand : public AbstractCommand {
public:
	DisplayCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~DisplayCommand() = default;
private:
	AbstractFileSystem* sys;
};