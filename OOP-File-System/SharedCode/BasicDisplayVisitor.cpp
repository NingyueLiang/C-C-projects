//Lab 5 FL & JP This file defines basic display visitor functionality

#include "BasicDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>
#include <string>
using namespace std;

void BasicDisplayVisitor::visit_TextFile(TextFile* f) {
	for (auto& c : f->read()) {
		std::cout << c;
	}
	std::cout << "\n";
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* f) {
	int n = sqrt(f->getSize());
	vector<char> contents = f->read();
	for (int y = n - 1; y >= 0; --y) {
		for (int x = 0; x < n; ++x) {
			std::cout << contents[y * n + x];
		}
		std::cout << "\n";
	}
}

bool BasicDisplayVisitor::search_TextFile(TextFile*, std::string) {
	return false;
}

bool BasicDisplayVisitor::search_ImageFile(ImageFile*, std::string) {
	return false;
}