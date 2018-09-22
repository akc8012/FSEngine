#pragma once
#include <typeinfo>
#include "ComponentType.h"

#include <string>
#include <memory>
using std::string;
using std::unique_ptr;
using std::make_unique;

class Component
{
public:
	virtual ~Component();
};
