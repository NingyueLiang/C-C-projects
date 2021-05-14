#pragma once

#include "AbstractParsingStrategy.h"

class RenameParsingStrategy : public AbstractParsingStrategy {
	std::vector<std::string> parse(std::string) override;
};