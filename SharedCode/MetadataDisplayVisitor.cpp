
#include "MetadataDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>

using namespace std;

void MetadataDisplayVisitor::visit_TextFile(TextFile* f) {
	cout << "name: " << f->getName() << endl;
	cout << "size: " << f->getSize() << endl;
	cout << "type: " << "text" << endl;

}

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* f) {
	cout << "name: " << f->getName() << endl;
	cout << "size: " << f->getSize() << endl;
	cout << "type: " << "image" << endl;
}