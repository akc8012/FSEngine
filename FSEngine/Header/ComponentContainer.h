#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

class ComponentContainer
{
public:
	ComponentContainer();

	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Shading>> shading;
	unique_ptr<ComponentCollection<Transform>> transform;

	template <typename T>
	T* GetComponent(const string& key, const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& key, const string& name = "") const;
};

template<typename T>
T* ComponentContainer::GetComponent(const string& key, const string& name) const
{
	auto component = TryGetComponent<T>(key, name);
	if (component == nullptr)
		throwFS("Could not find component on key \"" + key + "\" with name \"" + name + "\"");

	return component;
}

template<typename T>
T* ComponentContainer::TryGetComponent(const string& key, const string& name) const
{
	if (T::ComponentTypeId == Mesh::ComponentTypeId)
		return reinterpret_cast<T*>(name == "" ? mesh->TryGet(key) : mesh->TryGet(key, name));

	if (T::ComponentTypeId == Shading::ComponentTypeId)
		return reinterpret_cast<T*>(name == "" ? shading->TryGet(key) : shading->TryGet(key, name));

	if (T::ComponentTypeId == Transform::ComponentTypeId)
		return reinterpret_cast<T*>(name == "" ? transform->TryGet(key) : transform->TryGet(key, name));

	throwFS("Unknown type used for GetComponent");
}
