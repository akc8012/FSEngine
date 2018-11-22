#pragma once
#include <string>

using std::string;

class INameable
{
public:
	virtual ~INameable()
	{

	}

	virtual const string& GetName() const = 0;
	virtual void SetName(const string& name) = 0;
};
