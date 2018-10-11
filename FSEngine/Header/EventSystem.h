#pragma once
#include "IEventListener.h"
#include "FSDebug.h"

#include <map>
#include <vector>
#include <string>
using std::multimap;
using std::vector;
using std::string;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class EventSystem
{
private:
	multimap<string, IEventListener*> listeners;

public:
	void AddListener(const string& key, IEventListener* listener);
	void SendEvent(const string& key, const json& event);
};
