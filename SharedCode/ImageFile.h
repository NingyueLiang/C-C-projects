#pragma once
//Lab5: FL & JP: this file defines image file type
#include "AbstractFile.h"

class ImageFile : public AbstractFile {
public:
	ImageFile(std::string n);
	std::vector<char> read() override;
	int write(std::vector<char> w) override;
	int append(std::vector<char> a) override;
	unsigned int getSize() override;
	std::string getName() override;
	void accept(AbstractFileVisitor*) override;
	AbstractFile* clone(std::string in) override;
protected:
	std::vector<char> contents;
	std::string name;
	char size;
};