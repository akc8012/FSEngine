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

public:
	GameObject(FileSystem* fileSystem);
	~GameObject();

	void AddComponent(Component* component);
	template <typename T> T* GetComponent();

	virtual void Update(float deltaTime);
};

template <typename T> inline T* GameObject::GetComponent()
{
	for (const auto& component : components)
	{
		if (component->IsType(typeid(const T*)))
			return dynamic_cast<T*>(component);
	}

	return nullptr;
}
