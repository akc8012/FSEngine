#pragma once
#include <typeinfo>

class Component
{
private:
	bool isShared = false;

public:
	virtual const type_info& GetType() const = 0;
	bool IsType(const type_info& typeInfo);

	bool IsShared() const;
	void SetShared(bool isShared);
};
