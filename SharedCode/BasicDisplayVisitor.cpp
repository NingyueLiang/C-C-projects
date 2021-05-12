#include "BasicDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>

using namespace std;

class TextFile;
class ImageFile;

void BasicDisplayVisitor::visit_TextFile(TextFile* f) {
	for (auto& c : f->read()) {
		std::cout << c;
	}
	std::cout << "\n";
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* f) {
	int n = f->getSize() - '0';
	vector<char>& contents = f->read();
	for (int y = n - 1; y >= 0; --y) {
		for (int x = 0; x < n; ++x) {
			std::cout << contents[y * n + x];
		}
		std::cout << "\n";
	}

}

