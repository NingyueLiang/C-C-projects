#pragma once

#include "AbstractFileSystem.h"
#include <map>
#include <set>

class SimpleFileSystem : public AbstractFileSystem {
public:
	int addFile(std::string, AbstractFile*) override;
	int deleteFile(std::string) override;
	AbstractFile* openFile(std::string) override;
	int closeFile(AbstractFile*) override;
	std::set<std::string> getFileNames() override;
protected:
	std::map<std::string, AbstractFile*> files;
	std::set<AbstractFile*> open;
};
