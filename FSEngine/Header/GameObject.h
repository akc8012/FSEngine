#pragma once
#include "FSException.h"
#include "Systems.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "Components.h"
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
	string name;
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	unordered_map<string, shared_ptr<Mesh>> meshComponents;
	unordered_map<string, shared_ptr<Shading>> shadingComponents;
	unordered_map<string, shared_ptr<Transform>> transformComponents;

	void SetDefaultParameters();
	void ThrowDuplicateNameException(const string& name) const;

protected:
	Systems* systems = nullptr;
	GameObjectContainer* gameObjectContainer = nullptr;
	Components* components = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer, Components* components);

	virtual void Start();
	virtual void Update();

	const shared_ptr<Mesh>& AddComponent(const shared_ptr<Mesh>& component, const string& name = Types::ComponentTypeString[Mesh::ComponentTypeId]);
	const shared_ptr<Shading>& AddComponent(const shared_ptr<Shading>& component, const string& name = Types::ComponentTypeString[Shading::ComponentTypeId]);
	const shared_ptr<Transform>& AddComponent(const shared_ptr<Transform>& component, const string& name = Types::ComponentTypeString[Transform::ComponentTypeId]);

	template <typename T> shared_ptr<T> GetComponent(const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> shared_ptr<T> TryGetComponent(const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
	template <typename T> const unordered_map<string, shared_ptr<T>>& GetComponents() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	string GetName() const;
	void SetName(const string& name);

	json GetJson() const;
	void SetFromJson(const json& j);
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
	if (typeid(T) == typeid(Mesh))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(meshComponents);

	if (typeid(T) == typeid(Shading))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(shadingComponents);

	if (typeid(T) == typeid(Transform))
		return reinterpret_cast<const unordered_map<string, shared_ptr<T>>&>(transformComponents);

	throwFS("Unrecognized component type");
}
#pragma endregion

#pragma region GameObjectContainer
class GameObject::GameObjectContainer
{
private:
	Systems* systems = nullptr;
	Components* components = nullptr;

	unique_ptr<GameObjectMapper> gameObjectMapper;
	vector<unique_ptr<GameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);
	GameObject* TryGetGameObjectAtIndex(int index) const;

	void ReMapGameObjectNames(int startIndex);

public:
	GameObjectContainer(Systems* systems, Components* components);

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;
	template <typename T> T* GetGameObjectAs(const string& name) const;

	const vector<unique_ptr<GameObject>>& GetGameObjects() const;
};

template <typename T> T* GameObject::GameObjectContainer::GetGameObjectAs(const string& name) const
{
	return dynamic_cast<T*>(GetGameObject(name));
}
#pragma endregion
