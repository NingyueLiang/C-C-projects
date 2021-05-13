#pragma once

#include <vector>
#include <string>

class AbstractFileVisitor;

class AbstractFile {
public:
	virtual ~AbstractFile() = default;
	virtual std::vector<char> read() = 0;
	virtual int write(std::vector<char> w) = 0;
	virtual int append(std::vector<char> a) = 0;
	virtual unsigned int getSize() = 0;
	virtual std::string getName() = 0;
	virtual void accept(AbstractFileVisitor*) = 0;
};