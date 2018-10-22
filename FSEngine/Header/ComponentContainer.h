#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

class ComponentContainer
{
private:
	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Shading>> shading;
	unique_ptr<ComponentCollection<Transform>> transform;

public:
	ComponentContainer()
	{
		mesh = make_unique<ComponentCollection<Mesh>>();
		shading = make_unique<ComponentCollection<Shading>>();
		transform = make_unique<ComponentCollection<Transform>>();
	}

	template <typename T>
	ComponentCollection<T>* GetCollectionOfType(Types::ComponentType type) const;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");

	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;
	template <typename T>
	bool HasComponent(Types::ComponentType type, const string& name = "") const;

	template <typename T>
	vector<T*> GetComponents() const;
};

template<typename T>
ComponentCollection<T>* ComponentContainer::GetCollectionOfType(Types::ComponentType type) const
{
	switch (type)
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

template <typename T>
T* ComponentContainer::AddComponent(shared_ptr<T> component, const string& name)
{
	return name == "" ? GetCollectionOfType<T>(component->GetComponentTypeId())->Add(component) : GetCollectionOfType<T>(component->GetComponentTypeId())->Add(component, name);
}

template <typename T>
T* ComponentContainer::GetComponent(const string& name) const
{
	auto component = TryGetComponent<T>(name);
	if (component == nullptr)
		throwFS("Could not find component with name \"" + name + "\"");

	return component;
}

template <typename T>
T* ComponentContainer::TryGetComponent(const string& name) const
{
	return name == "" ? GetCollectionOfType<T>(T::ComponentTypeId)->TryGet() : GetCollectionOfType<T>(T::ComponentTypeId)->TryGet(name);
}

template <typename T>
bool ComponentContainer::HasComponent(Types::ComponentType type, const string& name) const
{
	return (name == "" ? GetCollectionOfType<T>(type)->TryGet() : GetCollectionOfType<T>(type)->TryGet(name)) != nullptr;
}

template <typename T>
vector<T*> ComponentContainer::GetComponents() const
{
	return GetCollectionOfType<T>(T::ComponentTypeId)->GetComponents();
}
