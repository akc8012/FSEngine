#pragma once
#include <typeinfo>
#include "ComponentType.h"

#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include <string>
#include <memory>
using std::string;
using std::unique_ptr;
using std::make_unique;

class Component
{
public:
	virtual ~Component();

	virtual json GetJson() const = 0;
	virtual void SetFromJson(const json& j) = 0;
};
