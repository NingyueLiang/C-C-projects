#pragma once
//Lab5 FL & PJ: this file defines ls command
#include "AbstractCommand.h"

class LSCommand : public AbstractCommand {
public:
	LSCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~LSCommand() = default;
private:
	AbstractFileSystem* sys;
};