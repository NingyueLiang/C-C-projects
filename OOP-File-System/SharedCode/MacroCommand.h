#pragma once
//Lab5 FL & PJ: this file defines macro command
#include "AbstractCommand.h"
#include "AbstractParsingStrategy.h"

class MacroCommand : public AbstractCommand {
public:
	MacroCommand(AbstractFileSystem* s);
	int execute(std::string in) override;
	void displayInfo() override;
	~MacroCommand() = default;
	void addCommand(AbstractCommand*);
	void setParseStrategy(AbstractParsingStrategy*);
private:
	std::vector<AbstractCommand*> commands;
	AbstractParsingStrategy* par;
	AbstractFileSystem* sys;
};
