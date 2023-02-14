//Lab 5 FL & JP This file defines search visitor functionality

#include "searchVisitor.h"
#include "../../SharedCode/TextFile.h"
#include "../../SharedCode/ImageFile.h"
#include <iostream>

using namespace std;

void searchVisitor::visit_TextFile(TextFile* f) {
	
}

void searchVisitor::visit_ImageFile(ImageFile* f) {
	
}

bool searchVisitor::search_TextFile(TextFile* in, std:: string target) {
	string total = "";
	for (auto& c : in->read()) {
		total = total + c;
	}
	if (total.find(target) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}

	
bool searchVisitor::search_ImageFile(ImageFile*, std::string target) {
	return false;
}