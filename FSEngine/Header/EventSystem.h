#pragma once
#include "IEventListener.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class EventSystem
{
private:
	vector<IEventListener*> listeners;

	vector<json> events;

public:
	void AddListener(IEventListener* listener);
	void SendEvent(const json& event);

	void AddEvent(const json& event);
	json ReadEvent();
	void ClearEvents();
};
