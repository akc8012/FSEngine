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
private:
	bool isShared = false;

public:
	virtual ~Component();
};
