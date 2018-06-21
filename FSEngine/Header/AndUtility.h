#pragma once
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class AndUtility
{
private:
	static string InternalTryLoadTextFromFile(const char* filepath, bool& success);

public:
	static string LoadTextFromFile(const char* filepath);
	static string TryLoadTextFromFile(const char* filepath);
};
