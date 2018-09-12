#pragma once
#include "FSException.h"
#include "FSDebug.h"

#include <string>
#include <fstream>
#include <sstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ios;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class FileSystem
{
private:
	json settingsJson = nullptr;

	static string InternalTryLoadTextFromFile(const string& filepath, bool& success);

public:
	FileSystem();

	static string LoadTextFromFile(const string& filepath);
	static string TryLoadTextFromFile(const string& filepath);

	void LoadSettingsFile();
	json GetSettingsValue(const string& key) const;
	template <typename T> T GetSettingsValue(const string& key) const;
};

template <typename T> T FileSystem::GetSettingsValue(const string& key) const
{
	return GetSettingsValue(key).get<T>();
}
