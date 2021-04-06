#pragma once
// declare AbstractFile here. As all methods are virtual and will not be defined, no .cpp file is necessary

#include "AbstractFile.h"

class TextFile : public AbstractFile {
public:
	TextFile(std::string n);
	void read() override;
	int write(std::vector<char> w) override;
	int append(std::vector<char> a) override;
	unsigned int getSize() override;
	std::string getName() override;
protected:
	std::vector<char> contents;
	std::string name;
};