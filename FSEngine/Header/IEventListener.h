#pragma once

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class IEventListener
{
public:
	virtual ~IEventListener()
	{

	}

	virtual void GetEvent(const json& event) = 0;
};
