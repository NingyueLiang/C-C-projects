#include "SimpleFileFactory.h"
#include "TextFile.h"
#include "ImageFile.h"

using namespace std;

AbstractFile* SimpleFileFactory::createFile(std::string name) {
	if (name.size() < 3) {
		return nullptr;
	}
	std::string tail = name.substr(name.size() - 3, name.size());
	if (tail == "txt") {
		TextFile* newFile = new TextFile(name);
		return newFile;
	}
	else if (tail == "img") {
		ImageFile* newFile = new ImageFile(name);
		return newFile;
	}
	else {
		return nullptr;
	}
}