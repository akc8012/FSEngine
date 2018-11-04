#pragma once
#include "FSException.h"
#include "FSDebug.h"

#include <string>
#include <fstream>
#include <sstream>
using std::string;
using std::ifstream;
using std::ofstream;

#include <nlohmann\json.hpp>
using json = nlohmann::json;
using nlohmann::detail::parse_error;

class FileSystem
{
private:
	json settingsJson;

public:
	FileSystem();

	static string LoadTextFromFile(const string& filepath);
	static string TryLoadTextFromFile(const string& filepath, bool& success);

	static void WriteTextToFile(const string& text, const string& filepath);

	void LoadSettingsFile();
	json GetSettingsValue(const string& key) const;

	template <typename T>
	T GetSettingsValue(const string& key) const;
};

template <typename T>
T FileSystem::GetSettingsValue(const string& key) const
{
	return GetSettingsValue(key).get<T>();
}
