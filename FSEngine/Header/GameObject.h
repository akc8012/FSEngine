#pragma once
#include "FSException.h"
#include "Systems.h"
#include "MeshComponent.h"
#include "ShadingComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObjectMapper.h"
#include "ParameterCollection.h"

#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;
using std::shared_ptr;
using std::make_shared;

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
	const string* name = nullptr;
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	unordered_map<string, shared_ptr<MeshComponent>> meshComponents;
	unordered_map<string, shared_ptr<ShadingComponent>> shadingComponents;
	unordered_map<string, shared_ptr<TransformComponent>> transformComponents;

	void SetDefaultParameters();
	void ThrowDuplicateNameException(const string& name) const;

protected:
	Systems* systems = nullptr;
	GameObjectContainer* gameObjectContainer = nullptr;

public:
	GameObject();

	void SetSystems(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer);

	virtual void Start();
	virtual void Update();

	const shared_ptr<MeshComponent>& AddComponent(const shared_ptr<MeshComponent>& component, const string& name = ComponentTypeString[MeshComponent::ComponentTypeId]);
	const shared_ptr<ShadingComponent>& AddComponent(const shared_ptr<ShadingComponent>& component, const string& name = ComponentTypeString[ShadingComponent::ComponentTypeId]);
	const shared_ptr<TransformComponent>& AddComponent(const shared_ptr<TransformComponent>& component, const string& name = ComponentTypeString[TransformComponent::ComponentTypeId]);

	template <typename T> shared_ptr<T> GetComponent(const string& name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> shared_ptr<T> TryGetComponent(const string& name = ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> const unordered_map<string, shared_ptr<T>>& GetComponents() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	const string& GetName() const;
	void SetName(const string& name);
};
#pragma endregion

#pragma region GetComponent
template <typename T> shared_ptr<T> GameObject::GetComponent(const string& name) const
{
	auto component = TryGetComponent<T>(name);
	if (component == nullptr)
		throwFS("Could not find component with name " + name);

	return component;
}

template <typename T> shared_ptr<T> GameObject::TryGetComponent(const string& name) const
{
	try
	{
		auto components = GetComponents<T>();
		return components.at(name);
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}

	return nullptr;
}

template <typename T> const unordered_map<string, shared_ptr<T>>& GameObject::GetComponents() const
{
	if (typeid(T) == typeid(MeshComponent))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(meshComponents);

	if (typeid(T) == typeid(ShadingComponent))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(shadingComponents);

	if (typeid(T) == typeid(TransformComponent))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(transformComponents);

	throwFS("Unrecognized component type");
}
#pragma endregion

#pragma region GameObjectContainer
class GameObject::GameObjectContainer
{
private:
	Systems* systems = nullptr;
	unique_ptr<GameObjectMapper> gameObjectMapper;
	vector<unique_ptr<GameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);
	GameObject* TryGetGameObjectAtIndex(int index) const;

public:
	GameObjectContainer(Systems* systems);

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;

	const vector<unique_ptr<GameObject>>& GetGameObjects() const;
};
#pragma endregion
