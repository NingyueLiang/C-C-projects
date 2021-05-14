#pragma once
//Lab5 : FL &JP THis file defines CP command
#include "AbstractCommand.h"

class CopyCommand : public AbstractCommand {
public:
	CopyCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~CopyCommand() = default;
private:
	AbstractFileSystem* sys;
};