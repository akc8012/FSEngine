#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class EventSystem
{
private:
	vector<json> events;

public:
	void AddEvent(const json& event);
	json ReadEvent();
	void ClearEvents();
};
