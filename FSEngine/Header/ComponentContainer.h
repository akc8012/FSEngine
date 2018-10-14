#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

class ComponentContainer
{
private:
	template <typename T>
	ComponentCollection<T>* GetCollectionOfType() const;

public:
	ComponentContainer()
	{
		mesh = make_unique<ComponentCollection<Mesh>>();
		shading = make_unique<ComponentCollection<Shading>>();
		transform = make_unique<ComponentCollection<Transform>>();
	}

	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Shading>> shading;
	unique_ptr<ComponentCollection<Transform>> transform;

	template <typename T>
	T* AddComponent(const string& key, shared_ptr<T> component, const string& name = "") const;

	template <typename T>
	T* GetComponent(const string& key, const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& key, const string& name = "") const;
};

template <typename T>
T* ComponentContainer::AddComponent(const string& key, shared_ptr<T> component, const string& name) const
{
	return name == "" ? GetCollectionOfType<T>()->Add(key, component) : GetCollectionOfType<T>()->Add(key, component, name);
}

template <typename T>
T* ComponentContainer::GetComponent(const string& key, const string& name) const
{
	auto component = TryGetComponent<T>(key, name);
	if (component == nullptr)
		throwFS("Could not find component on key \"" + key + "\" with name \"" + name + "\"");

	return component;
}

template <typename T>
T* ComponentContainer::TryGetComponent(const string& key, const string& name) const
{
	return name == "" ? GetCollectionOfType<T>()->TryGet(key) : GetCollectionOfType<T>()->TryGet(key, name);
}

template <typename T>
ComponentCollection<T>* ComponentContainer::GetCollectionOfType() const
{
	switch (T::ComponentTypeId)
	{
	case Mesh::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(mesh.get());

	case Shading::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(shading.get());

	case Transform::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(transform.get());

	default:
		throwFS("Unknown type used for GetCollectionOfType");
	}
}
