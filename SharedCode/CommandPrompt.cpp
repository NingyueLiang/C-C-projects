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
		return prompt::prompt_success;
	}
	else {
		return prompt::prompt_exist;
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
	cout << "$  ";
    getline(cin, in);
    return in;
}

int CommandPrompt::run() {
	while (1) {
		string in = prompt();
		if (in == "q") {
			return prompt::user_quit;
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
					cout << "Command input is invalid or empty!" << endl;
					
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
					    cout << "Command input is invalid!" << endl;
						
				    }
				}
				else {
					if (commands.find(first) != commands.end()) {
						latter = in.substr(in.find_first_of(' ') + 1, string::npos);
						if (commands[first]->execute(latter) != 0) {
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
	return prompt_success;
}

