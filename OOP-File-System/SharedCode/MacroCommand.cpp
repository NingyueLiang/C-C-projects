//Lab5 FL & PJ: this file defines macro command
#include "MacroCommand.h"

#include <iostream>
using namespace std;

MacroCommand::MacroCommand(AbstractFileSystem* s) : sys(s), par(nullptr) {}

void MacroCommand::displayInfo() {
	for (auto& command : commands) {
		command->displayInfo();
	}
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy* p) {
	this->par = p;
}

void MacroCommand::addCommand(AbstractCommand* c) {
	this->commands.push_back(c);
}

int MacroCommand::execute(std::string in) {
	vector<string> sep_in = par->parse(in);
	for (int i = 0; i < this->commands.size(); ++i) {
		int r = this->commands[i]->execute(sep_in[i]);
		if (r != command_success) {
			return command_fail;
		}
	}
	return command_success;
}