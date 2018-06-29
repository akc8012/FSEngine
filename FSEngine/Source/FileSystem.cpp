#include "../Header/FileSystem.h"

void FileSystem::LoadSettingsFile()
{
	string file = LoadTextFromFile("Resource/Json/settings.json");
	settingsJson = json::parse(file);
}

json FileSystem::GetSettingsValue(const char* key) const
{
	if (settingsJson == nullptr)
		throw (string)"Error: Attempting to access settings json without loading it first";

	return settingsJson[key];
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
