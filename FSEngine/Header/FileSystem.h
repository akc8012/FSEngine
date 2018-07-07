#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class FileSystem
{
private:
	json settingsJson = nullptr;

	static std::string InternalTryLoadTextFromFile(const char* filepath, bool& success);

public:
	FileSystem();

	static std::string LoadTextFromFile(const char* filepath);
	static std::string TryLoadTextFromFile(const char* filepath);

	void LoadSettingsFile();
	json GetSettingsValue(const char* key) const;
};
