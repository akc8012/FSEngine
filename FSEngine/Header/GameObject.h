#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"

class GameObject
{
protected:
	RenderComponent* renderComponent = nullptr;
	TransformComponent* transformComponent = nullptr;

public:
	GameObject();
	~GameObject();

	RenderComponent* GetRenderComponent();
	TransformComponent* GetTransformComponent();
	virtual void Update(Uint32 deltaTime);
};
