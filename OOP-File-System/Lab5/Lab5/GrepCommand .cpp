//Lab5 FL & PJ: this file defines Grep command for extra credit
#include "GrepCommand.h"
#include "searchVisitor.h"
#include <iostream>
#include <iomanip>

using namespace std;

GrepCommand::GrepCommand(AbstractFileSystem* s) : sys(s) { }

void GrepCommand::displayInfo() {
	cout << "GrepCommand will display names of all files which contains the given string in the file system, Grep can be invoked with the command: grep <string_to_search_for>" << endl;
}

int GrepCommand::execute(std::string in) {
	set<string> names = this->sys->getFileNames();
	std::set<std::string>::iterator it = names.begin();
	searchVisitor* s = new searchVisitor();
	while (it != names.end())
	{
		auto file = this->sys->openFile(*it);
		if (file->search_accept(s, in)) {
			cout << left << setw(20) << (*it) << endl;
		}
		this->sys->closeFile(file);
		it++;

	}

	return command_success;
}
