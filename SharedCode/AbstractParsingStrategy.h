#pragma once

#include <string>
#include <vector>

class AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string) = 0;
};