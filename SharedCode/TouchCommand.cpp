//Lab5 Frank Liang & Pan Joe: This file defines Touch command
#include "TouchCommand.h"
#include "PasswordProxy.h"
#include <iostream>
using namespace std;

TouchCommand::TouchCommand(AbstractFileSystem* s, AbstractFileFactory* f) : fac(f), sys(s) { }

void TouchCommand::displayInfo() {
	cout << "touch creates a file, touch can be invoked with the command Usage: touch <filename>" << endl;
}

int TouchCommand::execute(std::string filename){
	if(filename.substr(filename.length()-2) == "-p" ) {
		AbstractFile* a = this->fac->createFile(filename.substr(0, filename.find(" ")));
		if (a != nullptr) {
			cout << "What is the password?" << endl;
			string pw;
			getline(cin, pw);
			PasswordProxy* pi = new PasswordProxy(a, pw);
			int res = this->sys->addFile(filename.substr(0, filename.find(" ")), pi);
			if (res == command_success) {
				
				return command_success;
			}
			else {
				delete pi;
				return touch::cannot_add_file;
			}
		}
		else {
			return touch::cannot_create_file;
		}
	}
	else {
		AbstractFile* b = this->fac->createFile(filename);
		if (b != nullptr) {
			int res = this->sys->addFile(filename, b);
			if (res == command_success) {
				return command_success;
			}
			else {
				delete b;
				return touch::cannot_add_file;
			}
		}
		else {
			return touch::cannot_create_file;
		}

	}
}