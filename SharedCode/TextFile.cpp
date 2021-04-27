#include "TextFile.h"
#include <iostream>

TextFile::TextFile(std::string n)
	: name(n) {}

unsigned int TextFile::getSize() {
	return this->contents.size();
}

std::string TextFile::getName() {
	return this->name;
}

int TextFile::write(std::vector<char> w) {
	this->contents.clear();
	this->contents.assign(w.begin(), w.end());
	return 0;
}

int TextFile::append(std::vector<char> a) {
	this->contents.insert(contents.end(), a.begin(), a.end());
	return 0;
}

void TextFile::read() {
	for (auto &c : contents) {
		std::cout << c;
	}
	std::cout << "\n";
}