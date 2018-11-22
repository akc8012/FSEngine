#pragma once

#include <nlohmann\json.hpp>
using json = nlohmann::json;

class ISerializable
{
public:
	virtual ~ISerializable()
	{

	}

	virtual json GetJson() const = 0;
	virtual void SetFromJson(const json& j) = 0;

	virtual void SetSerializable(bool serializable) = 0;
	virtual bool GetSerializable() const = 0;
};
