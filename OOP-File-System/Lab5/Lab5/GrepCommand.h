#pragma once
//Lab5 FL & PJ: this file defines Grep command for extra credit
#include "../../SharedCode/AbstractCommand.h"
class GrepCommand : public AbstractCommand {
public:
	GrepCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~GrepCommand() = default;
private:
	AbstractFileSystem* sys;
};