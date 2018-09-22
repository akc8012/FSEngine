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

json FileSystem::GetSettingsValue(const string& key) const
{
	if (settingsJson == nullptr)
		throwFS((string)"Attempting to access settings json without loading it first");

	auto jsonValue = settingsJson.find(key);
	if (jsonValue == settingsJson.end())
		throwFS((string)"Could not retrieve settings value using key: " + key);

	return jsonValue.value();
}

string FileSystem::LoadTextFromFile(const string& filepath)
{
	bool success = false;
	string file = TryLoadTextFromFile(filepath, success);
	if (!success)
		throwFS("Unable to load text file from path: " + filepath);

	return file;
}

string FileSystem::TryLoadTextFromFile(const string& filepath, bool& success)
{
	ifstream inputStream(filepath, std::ios::in | std::ios::binary);
	success = (bool)inputStream;

	return success ? string((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>()) : "";
}

void FileSystem::WriteTextToFile(const string& text, const string& filepath)
{
	bool fileExists = false;
	TryLoadTextFromFile(filepath, fileExists);
	if (!fileExists)
		throwFS("Cannot write to text file at path: " + filepath);

	ofstream outputStream;
	outputStream.open(filepath);
	outputStream << text;
	outputStream.close();
}
