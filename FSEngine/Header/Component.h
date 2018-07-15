#pragma once
#include <typeinfo>
#include "ComponentType.h"

#include <string>
using std::string;

class Component
{
private:
	bool isShared = false;

public:
	virtual ~Component();

	bool IsShared() const;
	void SetShared(bool isShared);
};
