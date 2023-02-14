//Lab5: Fl&JP This file defines PasswordProxy functionality
#include "PasswordProxy.h"
#include <iostream>

PasswordProxy::PasswordProxy(AbstractFile* file, std::string pw) : realFile(file), password(pw) {}

PasswordProxy::~PasswordProxy() {
	delete realFile;
}

std::string PasswordProxy::passwordPrompt() {
	std::cout << "Please enter the password!" << std::endl;
	std::string input;
	std::getline(std::cin,input);

	return input;
}

bool PasswordProxy::isChecked(std::string in) {
	if (in == this->password) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<char> PasswordProxy::read() {
	std::string pw = this->passwordPrompt();
	if (this->isChecked(pw)) {
		return this->realFile->read();
	}
	else {
		std::vector<char> a = {};
		return a;
	}
}

int PasswordProxy::write(std::vector<char> in) {
	std::string pw = this->passwordPrompt();
	if (this->isChecked(pw)) {
		return this->realFile->write(in);
	}
	else {
		return passWord::invalidpw_for_write;
	}
}

int PasswordProxy::append(std::vector<char> in) {
	std::string pw = this->passwordPrompt();
	if (this->isChecked(pw)) {
		return this->realFile->append(in);
	}
	else {
		return passWord::invalidpw_for_append;
	}
}

unsigned int PasswordProxy::getSize() {
	return this->realFile->getSize();
}

std::string PasswordProxy::getName() {
	return this->realFile->getName();
}

void PasswordProxy::accept(AbstractFileVisitor* a) {
	std::string pw = this->passwordPrompt();
	if (this->isChecked(pw)) {
		return this->realFile->accept(a);
	}
}

bool PasswordProxy::search_accept(AbstractFileVisitor* a, std::string in) {
	std::string pw = this->passwordPrompt();
	if (this->isChecked(pw)) {
		return this->realFile->search_accept(a,in);
	}
	else {
		return false;
	}
}

AbstractFile* PasswordProxy::clone(std::string in) {
	return new PasswordProxy(this->realFile->clone(in), this->password);
}