#include "../Header/FileSystem.h"

FileSystem::FileSystem()
{
	LoadSettingsFile();
}

void FileSystem::LoadSettingsFile()
{
	string file = LoadTextFromFile("Resource/Json/settings.json");
	settingsJson = json::parse(file);
}

json FileSystem::GetSettingsValue(const char* key) const
{
	if (settingsJson == nullptr)
		throw (string)"Error: Attempting to access settings json without loading it first";

	auto jsonValue = settingsJson.find(key);
	if (jsonValue == settingsJson.end())
		throw (string)"Error: Could not retrieve settings value using key: " + key;

	return jsonValue.value();
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
	using std::fstream;
	using std::ifstream;
	using std::ios;

	ifstream inputStream(filepath, ios::in | ios::binary);
	
	success = (bool)inputStream;
	return success ? string((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>()) : "";
}
