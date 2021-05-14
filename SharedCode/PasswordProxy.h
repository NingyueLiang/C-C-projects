//Lab5: Fl&JP This file declares PasswordProxy class

#pragma once
#include "AbstractFile.h"
#include<vector>

class PasswordProxy : public AbstractFile {
	
public:
	PasswordProxy(AbstractFile* file, std::string pw);
	~PasswordProxy();

	std::vector<char> read() override;
	int write(std::vector<char>) override;
	int append(std::vector<char>) override;
	unsigned int getSize() override;
	std::string getName() override;
	void accept(AbstractFileVisitor*) override;
	AbstractFile* clone(std::string in) override;
protected:
	std::string passwordPrompt();
	bool isChecked(std::string in);

private:
	AbstractFile* realFile;
	std::string password;
	
};

enum passWord {invalidpw_for_write = 50, invalidpw_for_append = 51};