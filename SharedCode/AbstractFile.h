#pragma once
// declare AbstractFile here. As all methods are virtual and will not be defined, no .cpp file is necessary

#include <vector>
#include <string>

class AbstractFile {
public:
	virtual void read();
	virtual int write(std::vector<char> w);
	virtual int append(std::vector<char> a);
	virtual unsigned int getSize();
	virtual std::string getName();
};