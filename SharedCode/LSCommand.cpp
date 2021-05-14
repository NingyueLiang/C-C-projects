//Lab5 FL & PJ: this file defines ls command
#include "LSCommand.h"
#include "MetadataDisplayVisitor.h"
#include <iostream>
#include <iomanip>

using namespace std;

LSCommand::LSCommand(AbstractFileSystem* s) : sys(s) { }

void LSCommand::displayInfo() {
	cout << "LSCommand will display names of all files in the file system, LS can be invoked with the command: ls (with additional option, '-m', which will display asingle file per line along with the metadata associated with that file)" << endl;
}

int LSCommand::execute(std::string in) {
	if (in == "") {
		set<string> names = sys->getFileNames();
		std::set<std::string>::iterator it = names.begin();
		
		while (it != names.end())
		{
			cout << left << setw(20) << (*it);
			it++;
			if (it != names.end()) {
				cout << left << setw(20) << (*it);
				it++;
			}
			cout << endl;
			
		}

		return command_success;
	}
	else if (in == "-m") {
		set<string> names = this->sys->getFileNames();
		std::set<std::string>::iterator it = names.begin();
		MetadataDisplayVisitor* m = new MetadataDisplayVisitor();
		while (it != names.end())
		{
			this->sys->openFile(*it)->accept(m);
			it++;
		}

		return command_success;
	}
	else {
		return command_fail;
	}
}