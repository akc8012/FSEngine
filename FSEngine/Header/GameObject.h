#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"
#include "MeshComponent.h"
#include "ShadingComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObjectMapper.h"

#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;

class GameObject
{
public:
	class GameObjectContainer
	{
	private:
		GameObjectMapper* gameObjectMapper = nullptr;
		vector<GameObject*> gameObjects;

	public:
		GameObjectContainer();
		~GameObjectContainer();

		GameObject* AddGameObject(const string& name, GameObject* gameObject);

		GameObject* GetGameObject(const string& name) const;
		GameObject* GetGameObjectAtIndex(int index) const;
		vector<GameObject*> GetGameObjects() const;
	};

private:
	unordered_map<string, MeshComponent*>* meshComponents = nullptr;
	unordered_map<string, ShadingComponent*>* shadingComponents = nullptr;
	unordered_map<string, TransformComponent*>* transformComponents = nullptr;
	bool lateRefresh = false;

	void ThrowDuplicateNameException(const string& name) const;

protected:
	GameObjectContainer* gameObjectContainer = nullptr;
	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	Window* window = nullptr;

public:
	GameObject();
	~GameObject();

	void SetSystems(GameObject::GameObjectContainer* gameObjectContainer, FileSystem* fileSystem, Input* input, Window* window);
	virtual void Start();

	MeshComponent* AddComponent(MeshComponent* component, string name = ComponentTypeString[MeshComponent::ComponentTypeId]);
	ShadingComponent* AddComponent(ShadingComponent* component, string name = ComponentTypeString[ShadingComponent::ComponentTypeId]);
	TransformComponent* AddComponent(TransformComponent* component, string name = ComponentTypeString[TransformComponent::ComponentTypeId]);

	template <typename T> T* GetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> T* TryGetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> unordered_map<string, T*>* GetComponents() const;
	virtual void Update(float deltaTime);

	void SetLateRefresh(bool lateRefresh);
	bool GetLateRefresh() const;
};

template <typename T> inline T* GameObject::GetComponent(string name) const
{
	T* component = TryGetComponent<T>(name);
	if (component == nullptr)
		throw (string)"Could not find component with name " + name;

	return component;
}

template <typename T> inline T* GameObject::TryGetComponent(string name) const
{
	try
	{
		if (meshComponents->size() > 0 && typeid(T) == typeid(MeshComponent))
			return reinterpret_cast<T*>(meshComponents->at(name));

		if (shadingComponents->size() > 0 && typeid(T) == typeid(ShadingComponent))
			return reinterpret_cast<T*>(shadingComponents->at(name));

		if (transformComponents->size() > 0 && typeid(T) == typeid(TransformComponent))
			return reinterpret_cast<T*>(transformComponents->at(name));
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}

	return nullptr;
}

template <typename T> inline unordered_map<string, T*>* GameObject::GetComponents() const
{
	if (typeid(T) == typeid(MeshComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(meshComponents);

	if (typeid(T) == typeid(ShadingComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(shadingComponents);

	if (typeid(T) == typeid(TransformComponent))
		return reinterpret_cast<unordered_map<string, T*>*>(transformComponents);

	throw "Unrecognized type";
}
