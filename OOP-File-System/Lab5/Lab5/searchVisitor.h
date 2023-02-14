#pragma once
//Lab 5 FL & JP This file defines basic display visitor class
#include "../../SharedCode/AbstractFileVisitor.h"

class searchVisitor : public AbstractFileVisitor {
public:
	void visit_TextFile(TextFile*) override;
	void visit_ImageFile(ImageFile*) override;
	bool search_TextFile(TextFile*, std::string) override;
	bool search_ImageFile(ImageFile*, std::string) override;
};