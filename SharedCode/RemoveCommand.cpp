//Lab5 FL & PJ: this file defines remove command
#include "RemoveCommand.h"

#include <iostream>
using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* s) : sys(s) { }

void RemoveCommand::displayInfo() {
	cout << "RemoveCommand will remove the file with the provided name from the file system: rm <filename>" << endl;
}

int RemoveCommand::execute(std::string in) {
	if (sys->deleteFile(in) == exe_success) {
		return command_success;
	}
	else {
		return command_fail;
	}
}