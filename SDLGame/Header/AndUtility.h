#pragma once
#include <string>
using namespace std;

class AndUtility
{
private:
	static string internalTryLoadTextFromFile(const char* filepath, bool& success);

public:
	static string loadTextFromFile(const char* filepath);
	static string tryLoadTextFromFile(const char* filepath);
};
