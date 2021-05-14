//Lab5 FL & PJ: this file defines remove command
#include "CatCommand.h"
#include "BasicDisplayVisitor.h"
#include <iostream>
using namespace std;

CatCommand::CatCommand(AbstractFileSystem* s) : sys(s) { }

void CatCommand::displayInfo() {
	cout << "CatCommand will add a new command to your program: cat <filename> [-a]" << endl;
}

int CatCommand::execute(std::string in) {
	string in1 = in.substr(0, in.find(' '));
	string in2 = in.substr(in.find(' ') + 1, in.size());
	if (in2 == "-a") {
		AbstractFile* file = sys->openFile(in1);
		AbstractFileVisitor* vis = new BasicDisplayVisitor();
		file->accept(vis);
		cout << "" << endl;
		cout << "Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving." << endl;
		string line = "";
		string wr = "";
		do {
			wr += line + "\n";
			getline(cin, line);
		} while (line != ":q" && line != ":wq");
		if (line == ":q") {
			sys->closeFile(file);
		}
		else {
			vector<char> vwr(wr.begin(), wr.end());
			file->append(vwr);
			sys->closeFile(file);
		}
		return command_success;
	}
	else if (in2 == "") {
		AbstractFile* file = sys->openFile(in1);
		AbstractFileVisitor* vis = new BasicDisplayVisitor();
		file->accept(vis);
		cout << "Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving." << endl;
		string line = "";
		string wr = "";
		do {
			wr += line + " ";
			getline(cin, line);
		} while (line != ":q" && line != ":wq");
		if (line == ":q") {
			sys->closeFile(file);
		}
		else {
			vector<char> vwr(wr.begin(), wr.end());
			file->write(vwr);
			sys->closeFile(file);
		}
		return command_success;
	}
	else {
		return command_fail;
	}
}