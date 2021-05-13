//Lab5 Frank Liang & Pan Joe: This file defines Touch command
#include "TouchCommand.h"
#include <iostream>
using namespace std;
TouchCommand::TouchCommand(AbstractFileFactory* f, AbstractFileSystem* s) : fac(f), sys(s) { }

void TouchCommand::displayInfo() {
	cout << "touch creates a file, touch can be invoked with the command Usage: touch <filename>" << endl;
}

int TouchCommand::execute(std::string filename){
	AbstractFile* a = this->fac->createFile(filename);
	if (a != nullptr) {
		int res = this->sys->addFile(filename, a);
		if (res == touch::success) {
			return touch::success;
		}
		else {
			delete a;
			return touch::cannot_add_file;
		}
	}
	else {
		return touch::cannot_create_file;
	}

}