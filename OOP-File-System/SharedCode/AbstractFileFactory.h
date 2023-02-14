#pragma once
//Lab 5 FL & JP This file defines the interface for file factory
#include "AbstractFile.h"

class AbstractFileFactory {
public:
	virtual AbstractFile* createFile(std::string) = 0;
};

