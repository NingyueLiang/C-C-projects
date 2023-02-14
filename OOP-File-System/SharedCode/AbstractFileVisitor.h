#pragma once
//Lab 5 FL & JP This file defines the interface for file visitor
#include <string>;

class TextFile;
class ImageFile;


class AbstractFileVisitor {
public:
	virtual void visit_TextFile(TextFile*) = 0;
	virtual void visit_ImageFile(ImageFile*) = 0;
	virtual bool search_TextFile(TextFile*, std::string) =0;
	virtual bool search_ImageFile(ImageFile*, std::string)=0;
};