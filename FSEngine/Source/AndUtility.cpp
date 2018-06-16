#include "../Header/AndUtility.h"
#include <fstream>
#include <sstream>

string AndUtility::loadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = internalTryLoadTextFromFile(filepath, success);
	if (!success)
		throw (string)"Unable to load text file from path: " + filepath;

	return file;
}

string AndUtility::tryLoadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = internalTryLoadTextFromFile(filepath, success);
	if (!success)
		printf("Warning: Unable to load text file from path: %s", filepath);

	return file;
}

string AndUtility::internalTryLoadTextFromFile(const char* filepath, bool& success)
{
	ifstream inputStream(filepath, ios::in | ios::binary);
	
	success = (bool)inputStream;
	return success ? string((istreambuf_iterator<char>(inputStream)), istreambuf_iterator<char>()) : "";
}
