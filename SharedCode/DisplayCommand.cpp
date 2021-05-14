//Lab5 FL & PJ: this file defines ls command
#include "DisplayCommand.h"
#include "BasicDisplayVisitor.h"
#include <iostream>
#include <iomanip>

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* s) : sys(s) { }

void DisplayCommand::displayInfo() {
	cout << "DisplayCommand will display content of the given file name, Display can be invoked with the command: ds (with additional option, '-d', which will display unformatted content of the file" << endl;
}

int DisplayCommand::execute(std::string in) {

	if (in.substr(in.length() - 2) == "-d") {
		string filename = in.substr(0, in.find_first_of(" "));
		AbstractFile* res = this->sys->openFile(filename);
		if (res != nullptr) {
			vector<char> content = res->read();
			for (auto it = begin(content); it != end(content); ++it) {
				cout << (*it);
			}
			this->sys->closeFile(res);
			return command_success;
		}
		else {
			return cannot_open_file;
		}
	
	}
	else {
		AbstractFile* res = this->sys->openFile(in);
		if (res != nullptr) {
			BasicDisplayVisitor* basic = new BasicDisplayVisitor();
			res->accept(basic);
			this->sys->closeFile(res);
			return command_success;
		}
		else {
			return cannot_open_file;
		}
	}
}
