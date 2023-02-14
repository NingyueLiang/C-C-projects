
#include "MetadataDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>
#include <iomanip>

using namespace std;

void MetadataDisplayVisitor::visit_TextFile(TextFile* f) {
	cout << left << setw(20) << f->getName();
	cout << left << setw(20) << "text";
	cout << left << setw(20) << f->getSize()<< endl;

}

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* f) {
	cout << left << setw(20) << f->getName();
	cout << left << setw(20) << "image";
	cout << left << setw(20) << f->getSize() << endl;
}

bool MetadataDisplayVisitor::search_TextFile(TextFile*, std::string) {
	return false;
}

bool MetadataDisplayVisitor::search_ImageFile(ImageFile*, std::string) {
	return false;
}
