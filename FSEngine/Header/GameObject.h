#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"
#include "MeshComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include <unordered_map>
using std::unordered_map;

class GameObject
{
protected:
	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	Window* window = nullptr;

private:
	unordered_map<string, MeshComponent*> meshComponents;
	unordered_map<string, TextureComponent*> textureComponents;
	unordered_map<string, TransformComponent*> transformComponents;

	void ThrowDuplicateNameException(const string& name) const;

public:
	GameObject(FileSystem* fileSystem, Input* input, Window* window);
	~GameObject();

	void AddComponent(MeshComponent* component, string name = ComponentTypeString[MeshComponent::ComponentTypeId]);
	void AddComponent(TextureComponent* component, string name = ComponentTypeString[TextureComponent::ComponentTypeId]);
	void AddComponent(TransformComponent* component, string name = ComponentTypeString[TransformComponent::ComponentTypeId]);

	template <typename T> T* GetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	virtual void Update(float deltaTime);
};

template <typename T> inline T* GameObject::GetComponent(string name) const
{
	T* component = nullptr;

	if (meshComponents.size() > 0 && typeid(T) == typeid(MeshComponent))
		component = reinterpret_cast<T*>(meshComponents.at(name));

	if (textureComponents.size() > 0 && typeid(T) == typeid(TextureComponent))
		component = reinterpret_cast<T*>(textureComponents.at(name));

	if (transformComponents.size() > 0 && typeid(T) == typeid(TransformComponent))
		component = reinterpret_cast<T*>(transformComponents.at(name));

	return component;
}
