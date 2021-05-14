#include "RenameParsingStrategy.h"

using  namespace std;

std::vector<std::string> RenameParsingStrategy::parse(std::string in) {
	string newn = in.substr(in.find(" ") + 1, in.size());
	vector<string> res;
	res.push_back(in);
	res.push_back(newn);
	return res;
}