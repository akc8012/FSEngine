#pragma once
#include <typeinfo>

class Component
{
public:
	virtual const type_info& GetType() const = 0;
	bool IsType(const type_info& typeInfo);
};
