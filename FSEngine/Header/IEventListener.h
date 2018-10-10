#pragma once

#include <string>
using std::string;

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class IEventListener
{
public:
	virtual ~IEventListener()
	{

	}

	virtual void ReceiveEvent(const string& name, const json& event) = 0;
};
