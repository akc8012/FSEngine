#pragma once
#include "RenderComponent.h"

class GameObject
{
protected:
	RenderComponent* renderComponent = NULL;

public:
	GameObject();
	~GameObject();
};
