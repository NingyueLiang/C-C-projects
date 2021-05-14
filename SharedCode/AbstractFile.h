#pragma once
//Lab5: FL & JP: this file defines interface for file type
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
	virtual AbstractFile* clone(std::string in) = 0;
};

enum system { exe_success = 0, exe_fail = 1, wrong_size = 2, invalid_input =3, invalid_call =4, already_exist = 5, not_file = 6, not_open = 8, not_exist = 9};