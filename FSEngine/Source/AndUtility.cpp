#include "../Header/AndUtility.h"
#include <fstream>
#include <sstream>

string AndUtility::LoadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		throw (string)"Unable to load text file from path: " + filepath;

	return file;
}

string AndUtility::TryLoadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		printf("Warning: Unable to load text file from path: %s", filepath);

	return file;
}

string AndUtility::InternalTryLoadTextFromFile(const char* filepath, bool& success)
{
	ifstream inputStream(filepath, ios::in | ios::binary);
	
	success = (bool)inputStream;
	return success ? string((istreambuf_iterator<char>(inputStream)), istreambuf_iterator<char>()) : "";
}
