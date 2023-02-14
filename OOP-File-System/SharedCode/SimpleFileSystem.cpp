//Lab 5 FL & JP This file defines the simple file system functionality
#include "SimpleFileSystem.h"

int SimpleFileSystem::addFile(std::string name, AbstractFile* file) {
	if (this->files.count(name) > 0) {
		return already_exist;
	}
	if (!file) {
		return not_file;
	}
	this->files.insert(std::pair<std::string, AbstractFile*>(name, file));
	return exe_success;
}

AbstractFile* SimpleFileSystem::openFile(std::string name) {
	if (this->files.find(name) == this->files.end()) {
		return nullptr;
	}
	else if (this->open.find(files[name]) != this->open.end()) {
		return nullptr;
	}
	else {
		this->open.insert(files[name]);
		return this->files[name];
	}
}

int SimpleFileSystem::closeFile(AbstractFile* file) {
	if (this->open.find(file) != this->open.end()) {
		open.erase(file);
		return exe_success;
	}
	else {
		return not_open;
	}
}

int SimpleFileSystem::deleteFile(std::string name) {
	if (this->files.count(name) == 0) {
		return not_exist;
	} else if (this->open.find(this->files[name]) != this->open.end()) {
		return not_exist;
	} else {
		AbstractFile* deleted = files[name];
		this->files.erase(name);
		delete deleted;
		return exe_success;
	}
}

std::set<std::string> SimpleFileSystem::getFileNames() {
	
	std::set<std::string> names = {};

	std::map<std::string, AbstractFile*>::iterator it;

	for (auto it = files.begin(); it != files.end(); it++)
	{
		names.insert(it->first);
	}

	return names;
}