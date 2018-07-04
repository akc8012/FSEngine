#pragma once
#include "FileSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

#include <vector>

class GameObject
{
protected:
	FileSystem* fileSystem = nullptr;

	std::vector<Component*> components;
	RenderComponent* renderComponent = nullptr;
	TransformComponent* transformComponent = nullptr;
	TextureComponent* textureComponent = nullptr;

public:
	GameObject(FileSystem* fileSystem);
	~GameObject();

	void AddComponent(Component* component);
	Component* GetComponent(const type_info& typeInfo) const;

	RenderComponent* GetRenderComponent() const;
	TransformComponent* GetTransformComponent() const;
	TextureComponent* GetTextureComponent() const;

	void SetRenderComponent(RenderComponent* renderComponent);
	void SetTransformComponent(TransformComponent* transformComponent);
	void SetTextureComponent(TextureComponent* textureComponent);

	virtual void Update(Uint32 deltaTime);
};
