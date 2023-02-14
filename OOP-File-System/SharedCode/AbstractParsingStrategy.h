#pragma once
//Lab 5 FL & JP This file defines the interface for AbstractParsingStrategy
#include <string>
#include <vector>

class AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string) = 0;
};