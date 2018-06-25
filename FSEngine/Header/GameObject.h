#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"

class GameObject
{
protected:
	RenderComponent* renderComponent = NULL;
	TransformComponent* transformComponent = NULL;

public:
	GameObject();
	~GameObject();

	//to-do: change this to one template GetComponent
	RenderComponent* GetRenderComponent();
	TransformComponent* GetTransformComponent();
	virtual void Update();
};
