#include "SimpleFileSystem.h"

int SimpleFileSystem::addFile(std::string name, AbstractFile* file) {
	if (this->files.count(name) > 0) {
		return 5;
	}
	if (!file) {
		return 6;
	}
	this->files.insert(std::pair<std::string, AbstractFile*>(name, file));
	return 0;
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
		return 0;
	}
	else {
		return 8;
	}
}

int SimpleFileSystem::deleteFile(std::string name) {
	if (this->files.count(name) == 0) {
		return 9;
	} else if (this->open.find(this->files[name]) != this->open.end()) {
		return 9;
	} else {
		AbstractFile* deleted = files[name];
		this->files.erase(name);
		delete deleted;
		return 0;
	}
}

