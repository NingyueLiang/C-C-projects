#pragma once

#include "AbstractFileVisitor.h"

class MetadataDisplayVisitor : public AbstractFileVisitor {
public:
	void visit_TextFile(TextFile*) override;
	void visit_ImageFile(ImageFile*) override;
};

