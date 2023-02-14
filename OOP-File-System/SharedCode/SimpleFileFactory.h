#pragma once
//Lab 5 FL & JP This file defines simple file factory class
#include "AbstractFileFactory.h"

class SimpleFileFactory : public AbstractFileFactory {
public:
	AbstractFile* createFile(std::string) override;
};
