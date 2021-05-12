#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\ImageFile.h"
#include <iostream>

using namespace std;

int main()
{
	AbstractFile* f = new TextFile("test");
	string s1 = "1";
	vector<char> v1(s1.begin(), s1.end());
	f->write(v1);
	vector<char> rf1 = f->read();

	string s2 = "2";
	vector<char> v2(s2.begin(), s2.end());
	f->write(v2);
	vector<char> rf2 = f->read();

	cout << rf1[0] << endl;
	cout << rf2[0] << endl;
}
