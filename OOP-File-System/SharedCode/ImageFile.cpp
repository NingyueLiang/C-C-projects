//Lab5: FL&JP: This file defines image file type.
#include "ImageFile.h"
#include "AbstractFileVisitor.h"
#include <iostream>

ImageFile::ImageFile(std::string n)
	: name(n), size(0) {}

unsigned int ImageFile::getSize() {
	return this->contents.size();
}

std::string ImageFile::getName() {
	return this->name;
}

int ImageFile::write(std::vector<char> w) {
	if (w.empty() || !isdigit(w.back())) {
		return exe_fail;
	}
	int n = pow((w.back() - '0'), 2) + 1;
	if (w.size() != n) {
		return wrong_size;
	}
	this->contents.clear();
	this->size = w.back();
	for (int i = 0; i < n - 1; ++i) {
		if (w[i] != 'X' && w[i] != ' ') {
			this->contents.clear();
			this->size = 0;
			return invalid_input;
		}
		this->contents.push_back(w[i]);
	}
	return exe_success;
}

int ImageFile::append(std::vector<char> a) {
	return invalid_call;
}

std::vector<char> ImageFile::read() {
	return this->contents;
}

void ImageFile::accept(AbstractFileVisitor* v) {
	v->visit_ImageFile(this);
}

AbstractFile* ImageFile::clone(std::string in) {
	
		ImageFile* img = new ImageFile(in);
		img->size = this->getSize();
		img->contents = this->contents;
		return img;

}
bool ImageFile::search_accept(AbstractFileVisitor* v, std::string in) {
	return v->search_ImageFile(this, in);
}