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
	unordered_map<string, MeshComponent*>* meshComponents = nullptr;
	unordered_map<string, TextureComponent*>* textureComponents = nullptr;
	unordered_map<string, TransformComponent*>* transformComponents = nullptr;

	void ThrowDuplicateNameException(const string& name) const;

public:
	GameObject(FileSystem* fileSystem, Input* input, Window* window);
	~GameObject();

	void AddComponent(MeshComponent* component, string name = ComponentTypeString[MeshComponent::ComponentTypeId]);
	void AddComponent(TextureComponent* component, string name = ComponentTypeString[TextureComponent::ComponentTypeId]);
	void AddComponent(TransformComponent* component, string name = ComponentTypeString[TransformComponent::ComponentTypeId]);

	template <typename T> T* GetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> unordered_map<string, T*>* GetComponents() const;
	virtual void Update(float deltaTime);
};

template <typename T> inline T* GameObject::GetComponent(string name) const
{
	if (meshComponents->size() > 0 && typeid(T) == typeid(MeshComponent))
		return reinterpret_cast<T*>(meshComponents->at(name));

	if (textureComponents->size() > 0 && typeid(T) == typeid(TextureComponent))
		return reinterpret_cast<T*>(textureComponents->at(name));

	if (transformComponents->size() > 0 && typeid(T) == typeid(TransformComponent))
		return reinterpret_cast<T*>(transformComponents->at(name));

	return nullptr;
}

template <typename T> inline unordered_map<string, T*>* GameObject::GetComponents() const
{
	if (typeid(T) == typeid(MeshComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(meshComponents);

	if (typeid(T) == typeid(TextureComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(textureComponents);

	if (typeid(T) == typeid(TransformComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(transformComponents);

	throw "Unrecognized type";
}
