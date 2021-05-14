#pragma once
//Lab 5 FL & JP This file defines meta display visitor class
#include "AbstractFileVisitor.h"

class MetadataDisplayVisitor : public AbstractFileVisitor {
public:
	void visit_TextFile(TextFile*) override;
	void visit_ImageFile(ImageFile*) override;
	bool search_TextFile(TextFile*, std::string) override;
	bool search_ImageFile(ImageFile*, std::string) override;
};
