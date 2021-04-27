#include "TextFile.h"
#include <iostream>

TextFile::TextFile(std::string n)
	: name(n) {}

unsigned int TextFile::getSize() {
	return static_cast<unsigned int>(contents.size());
}

std::string TextFile::getName() {
	return name;
}

int TextFile::write(std::vector<char> w) {
	contents.clear();
	contents.assign(w.begin(), w.end());
	return 0;
}

int TextFile::append(std::vector<char> a) {
	contents.insert(contents.end(), a.begin(), a.end());
	return 0;
}

void TextFile::read() {
	for (char c : contents) {
		std::cout << c;
	}
	std::cout << "\n";
}