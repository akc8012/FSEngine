#pragma once
#include <string>
#include <fstream>
#include <sstream>
using std::string;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class FileSystem
{
private:
	json settingsJson = nullptr;

	static string InternalTryLoadTextFromFile(const char* filepath, bool& success);

public:
	FileSystem();

	static string LoadTextFromFile(const char* filepath);
	static string TryLoadTextFromFile(const char* filepath);

	void LoadSettingsFile();
	json GetSettingsValue(const char* key) const;
	template <typename T> T GetSettingsValue(const char* key) const;
};

template <typename T> inline T FileSystem::GetSettingsValue(const char* key) const
{
	return GetSettingsValue(key).get<T>();
}
