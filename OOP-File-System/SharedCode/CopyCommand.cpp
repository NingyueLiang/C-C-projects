//Lab5 FL & PJ: this file defines cp command
#include "CopyCommand.h"
#include <iostream>
#include <sstream>

using namespace std;

CopyCommand::CopyCommand(AbstractFileSystem* s) : sys(s) { }

void CopyCommand::displayInfo() {
	cout << "CopyCommand will copy the given file and rename it with input string, cp <file_to_copy> <new_name_with_no_extension>" << endl;
}

int CopyCommand::execute(std::string in) {
	string ori, name;
	istringstream iss(in);
	iss >> ori >> name;
	name = name + ori.substr(ori.length()-4);
	
	auto original = this->sys->openFile(ori);
	if (original == nullptr) {
		cout << "Can't open file" << endl;
		return command_fail;
	}
	else {
		AbstractFile* copy = original->clone(name);

		int res = this->sys->addFile(copy->getName(), copy);
		this->sys->closeFile(original);
		if (res == exe_success) {
			return command_success;
		}
		else {
			delete copy;
			cout << "Can't add file to our system" << endl;
			return command_fail;
		}
	}

	
	
}
