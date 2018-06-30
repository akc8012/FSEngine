#pragma once
#include "FileSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class GameObject
{
protected:
	FileSystem* fileSystem = nullptr;
	RenderComponent* renderComponent = nullptr;
	TransformComponent* transformComponent = nullptr;

public:
	GameObject(FileSystem* fileSystem);
	~GameObject();

	RenderComponent* GetRenderComponent();
	TransformComponent* GetTransformComponent();
	virtual void Update(Uint32 deltaTime);
};
