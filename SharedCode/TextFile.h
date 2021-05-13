#pragma once

#include "AbstractFile.h"

class TextFile : public AbstractFile {
public:
	TextFile(std::string n);
	void read() override;
	int write(std::vector<char> w) override;
	int append(std::vector<char> a) override;
	unsigned int getSize() override;
	std::string getName() override;
	void accept(AbstractFileVisitor*) override;
protected:
	std::vector<char> contents;
	std::string name;
};