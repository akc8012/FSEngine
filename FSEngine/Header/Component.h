#pragma once
#include <typeinfo>
#include "ComponentType.h"

class Component
{
protected:
	ComponentType componentType;

private:
	bool isShared = false;

public:
	virtual ~Component();

	ComponentType GetType() const;

	bool IsShared() const;
	void SetShared(bool isShared);
};
