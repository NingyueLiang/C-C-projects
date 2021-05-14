#pragma once
//Lab5 FL & PJ: this file defines cat command
#include "AbstractCommand.h"

class CatCommand : public AbstractCommand {
public:
	CatCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~CatCommand() = default;
private:
	AbstractFileSystem* sys;
};

