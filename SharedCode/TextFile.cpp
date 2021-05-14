//Lab5 FL & JP This file defines text file class
#include "TextFile.h"
#include "AbstractFileVisitor.h"
#include <iostream>

using namespace std;

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
	return exe_success;
}

int TextFile::append(std::vector<char> a) {
	this->contents.insert(contents.end(), a.begin(), a.end());
	return exe_success;
}


AbstractFile* TextFile::clone(std::string in) {

	TextFile* txt = new TextFile(in);
	txt->contents = this->contents;
	return txt;

}

std::vector<char> TextFile::read() {
	return this->contents;
}

void TextFile::accept(AbstractFileVisitor* v) {
	v->visit_TextFile(this);
}

bool TextFile::search_accept(AbstractFileVisitor* v, string in) {
	return v->search_TextFile(this, in);
}