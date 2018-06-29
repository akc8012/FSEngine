#pragma once
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class FileSystem
{
private:
	json settingsJson = nullptr;

	static string InternalTryLoadTextFromFile(const char* filepath, bool& success);

public:
	static string LoadTextFromFile(const char* filepath);
	static string TryLoadTextFromFile(const char* filepath);

	void LoadSettingsFile();
	json GetSettingsValue(const char* key) const;
};
