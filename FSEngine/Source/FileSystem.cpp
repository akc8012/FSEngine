#include "../Header/FileSystem.h"

FileSystem::FileSystem()
{
	LoadSettingsFile();
}

void FileSystem::LoadSettingsFile()
{
	std::string file = LoadTextFromFile("Resource/Json/settings.json");
	settingsJson = json::parse(file);
}

json FileSystem::GetSettingsValue(const char* key) const
{
	if (settingsJson == nullptr)
		throw (std::string)"Error: Attempting to access settings json without loading it first";

	auto jsonValue = settingsJson.find(key);
	if (jsonValue == settingsJson.end())
		throw (std::string)"Error: Could not retrieve settings value using key: " + key;

	return jsonValue.value();
}

std::string FileSystem::LoadTextFromFile(const char* filepath)
{
	using std::string;

	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		throw (string)"Unable to load text file from path: " + filepath;

	return file;
}

std::string FileSystem::TryLoadTextFromFile(const char* filepath)
{
	using std::string;

	bool success = false;
	string file = InternalTryLoadTextFromFile(filepath, success);
	if (!success)
		printf("Warning: Unable to load text file from path: %s", filepath);

	return file;
}

std::string FileSystem::InternalTryLoadTextFromFile(const char* filepath, bool& success)
{
	std::ifstream inputStream(filepath, std::ios::in | std::ios::binary);
	
	success = (bool)inputStream;
	return success ? std::string((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>()) : "";
}
