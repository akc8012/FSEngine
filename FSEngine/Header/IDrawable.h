#pragma once
#include "Component.h"

class IDrawable : public Component
{
public:
	virtual ~IDrawable()
	{

	}

	virtual void BindTexture() = 0;
	virtual bool HasFlatColor() const = 0;
};
