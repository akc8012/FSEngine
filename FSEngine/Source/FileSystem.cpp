#include "../Header/FileSystem.h"

json FileSystem::GetSettingValue(const char* key)
{
	string file = LoadTextFromFile("Resource/Json/settings.json");
	json jsonFile = json::parse(file);
	return jsonFile[key];
}

string FileSystem::LoadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		throw (string)"Unable to load text file from path: " + filepath;

	return file;
}

string FileSystem::TryLoadTextFromFile(const char* filepath)
{
	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		printf("Warning: Unable to load text file from path: %s", filepath);

	return file;
}

string FileSystem::InternalTryLoadTextFromFile(const char* filepath, bool& success)
{
	ifstream inputStream(filepath, ios::in | ios::binary);
	
	success = (bool)inputStream;
	return success ? string((istreambuf_iterator<char>(inputStream)), istreambuf_iterator<char>()) : "";
}
