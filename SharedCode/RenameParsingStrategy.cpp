//Lab5 FL & PJ: this file defines rn functionality
#include "RenameParsingStrategy.h"

using  namespace std;

std::vector<std::string> RenameParsingStrategy::parse(std::string in) {
	string exi = in.substr(0, in.find(" "));
	vector<string> res;
	res.push_back(in);
	res.push_back(exi);
	return res;
}