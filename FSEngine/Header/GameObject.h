#pragma once
#include "FileSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

class GameObject
{
protected:
	FileSystem* fileSystem = nullptr;
	RenderComponent* renderComponent = nullptr;
	TransformComponent* transformComponent = nullptr;
	TextureComponent* textureComponent = nullptr;

public:
	GameObject(FileSystem* fileSystem);
	~GameObject();

	RenderComponent* GetRenderComponent() const;
	TransformComponent* GetTransformComponent() const;
	TextureComponent* GetTextureComponent() const;

	virtual void Update(Uint32 deltaTime);
};
