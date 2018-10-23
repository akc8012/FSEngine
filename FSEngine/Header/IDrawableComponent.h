#pragma once
#include "Component.h"

class IDrawableComponent : public Component
{
public:
	virtual ~IDrawableComponent()
	{

	}

	virtual void BindTexture() = 0;
	virtual bool HasFlatColor() const = 0;
};
