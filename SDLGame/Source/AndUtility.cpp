#include "../Header/AndUtility.h"
#include <fstream>
#include <sstream>

string AndUtility::tryLoadTextFromFile(const char * filepath)
{
	ifstream inputStream(filepath, ios::in | ios::binary);
	if (!inputStream)
		throw (string)"Unable to read file at path: " + filepath;

	return string((istreambuf_iterator<char>(inputStream)), istreambuf_iterator<char>());
}
