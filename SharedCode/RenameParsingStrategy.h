#pragma once
//Lab 5 FL & JP This file defines rename parsing strategy class
#include "AbstractParsingStrategy.h"

class RenameParsingStrategy : public AbstractParsingStrategy {
public:
	std::vector<std::string> parse(std::string) override;
};