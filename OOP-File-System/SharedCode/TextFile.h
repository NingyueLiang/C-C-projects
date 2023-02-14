#pragma once
//Lab5: FL&JP This file declare text file class
#include "AbstractFile.h"

class TextFile : public AbstractFile {
public:
	TextFile(std::string n);
	std::vector<char> read() override;
	int write(std::vector<char> w) override;
	int append(std::vector<char> a) override;
	unsigned int getSize() override;
	std::string getName() override;
	void accept(AbstractFileVisitor*) override;
	AbstractFile* clone(std::string in) override;
	bool search_accept(AbstractFileVisitor* , std::string) override;
protected:
	std::vector<char> contents;
	std::string name;
};