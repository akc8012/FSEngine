#pragma once
#include "ComponentType.h"

#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include <string>
#include <memory>
using std::string;
using std::to_string;
using std::unique_ptr;
using std::make_unique;

class Component
{
private:
	string name;

public:
	virtual ~Component();

	static const Types::ComponentType ComponentTypeId = Types::Component;
	virtual Types::ComponentType GetComponentTypeId() const;

	const string& GetName() const;
	void SetName(const string& name);

	virtual json GetJson() const = 0;
	virtual void SetFromJson(const json& j) = 0;
};
