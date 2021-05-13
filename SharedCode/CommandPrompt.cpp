#include "CommandPrompt.h"
#include <iostream>
#include <sstream>
using namespace std;

CommandPrompt::CommandPrompt() 
	: system(nullptr), factory(nullptr) {}

CommandPrompt::~CommandPrompt() {}

void CommandPrompt::setFileSystem(AbstractFileSystem* s) {
	this->system = s;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* f) {
	this->factory = f;
}

int CommandPrompt::addCommand(std::string s, AbstractCommand* c) {
	if (commands.find(s) == commands.end()) {
		commands.insert(std::pair<std::string, AbstractCommand*>(s, c));
		return 0;
	}
	else {
		return 63;
	}
	
}

void CommandPrompt::listCommands() {
	for (auto& command : this->commands) {
		cout << command.first << endl;
	}
}

std::string CommandPrompt::prompt() {
	string in;
	cout << "Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command." << endl;
	cout << "$";
    getline(cin, in);
    return in;
}

int CommandPrompt::run() {
	while (1) {
		string in = prompt();
		if (in == "q") {
			return 64;
		}
		else if (in == "help") {
			this->listCommands();
		}
		else { 
			if (in.find(" ") == in.npos) {
				if (commands.find(in) != commands.end()) {
					string s = "";
					if (commands[in]->execute(s) != 0) {
						cout << "Command execution failed!" << endl;
					}
				}
				else {
					cout << "Command is invalid!" << endl;
				}
			}
			else {
				string first, second, latter;
				istringstream iss(in);
				iss >> first;
				if (first == "help") {
					iss >> second;
					if (commands.find(second) != commands.end()) {
					    commands[second]->displayInfo();
				    }
				    else {
					    cout << "Command is invalid!" << endl;
				    }
				}
				else {
					if (commands.find(first) != commands.end()) {
						getline(iss, latter);
						if (int r = commands[first]->execute(latter) != 0) {
							cout << "Command execution failed!" << endl;
						}
					}
					else {
						cout << "Command is invalid!" << endl;
					}
				}
			}
		}
		cout << "" << endl;
	}	
}

