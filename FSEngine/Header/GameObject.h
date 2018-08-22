#pragma once
#include "Systems.h"
#include "MeshComponent.h"
#include "ShadingComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObjectMapper.h"

#include <unordered_map>
#include <vector>
#include <bitset>
using std::unordered_map;
using std::vector;
using std::bitset;

#pragma region GameObject
class GameObject
{
public:
	class GameObjectContainer;
	enum Parameters
	{
		DoUpdate,
		DoDraw,
		DoLateUpdate,
		DoLateDraw,

		ParametersLength
	};

private:
	bitset<Parameters::ParametersLength> parameters;

	unordered_map<string, MeshComponent*> meshComponents;
	unordered_map<string, ShadingComponent*> shadingComponents;
	unordered_map<string, TransformComponent*> transformComponents;

	void SetDefaultParameters();
	void ThrowDuplicateNameException(const string& name) const;

protected:
	Systems* systems = nullptr;
	GameObjectContainer* gameObjectContainer = nullptr;

public:
	GameObject();
	~GameObject();

	void SetSystems(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer);
	virtual void Start();

	MeshComponent* AddComponent(MeshComponent* component, string name = ComponentTypeString[MeshComponent::ComponentTypeId]);
	ShadingComponent* AddComponent(ShadingComponent* component, string name = ComponentTypeString[ShadingComponent::ComponentTypeId]);
	TransformComponent* AddComponent(TransformComponent* component, string name = ComponentTypeString[TransformComponent::ComponentTypeId]);

	template <typename T> T* GetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> T* TryGetComponent(string name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> const unordered_map<string, T*>& GetComponents() const;
	virtual void Update(float deltaTime);

	void SetParameter(Parameters parameter, bool value);
	bool GetParameter(Parameters parameter) const;
};
#pragma endregion

#pragma region GetComponent
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
		unordered_map<string, T*> components = GetComponents<T>();
		return components.at(name);
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}

	return nullptr;
}

template <typename T> inline const unordered_map<string, T*>& GameObject::GetComponents() const
{
	if (typeid(T) == typeid(MeshComponent))
		return reinterpret_cast<const unordered_map<string, T*>&>(meshComponents);

	if (typeid(T) == typeid(ShadingComponent))
		return reinterpret_cast<const unordered_map<string, T*>&>(shadingComponents);

	if (typeid(T) == typeid(TransformComponent))
		return reinterpret_cast<const unordered_map<string, T*>&>(transformComponents);

	throw (string)"Unrecognized component type";
}
#pragma endregion

#pragma region GameObjectContainer
class GameObject::GameObjectContainer
{
private:
	Systems* systems = nullptr;
	GameObjectMapper* gameObjectMapper = nullptr;
	vector<GameObject*> gameObjects;

	void InitializeGameObject(GameObject* gameObject);
	GameObject* TryGetGameObjectAtIndex(int index) const;

public:
	GameObjectContainer(Systems* systems);
	~GameObjectContainer();

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;

	const vector<GameObject*>& GetGameObjects() const;
};
#pragma endregion
