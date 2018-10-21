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

	template <typename T>
	ComponentCollection<T>* GetCollectionOfType() const;

	template <typename T>
	ComponentCollection<T>* GetCollectionOfType(T* component) const;

public:
	ComponentContainer()
	{
		mesh = make_unique<ComponentCollection<Mesh>>();
		shading = make_unique<ComponentCollection<Shading>>();
		transform = make_unique<ComponentCollection<Transform>>();
	}

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");

	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;

	template <typename T>
	vector<T*> GetComponents() const;
};

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

template<typename T>
ComponentCollection<T>* ComponentContainer::GetCollectionOfType(T* component) const
{
	if (component->GetComponentTypeId() == Mesh::ComponentTypeId)
		return reinterpret_cast<ComponentCollection<T>*>(mesh.get());

	else if (component->GetComponentTypeId() == Shading::ComponentTypeId)
		return reinterpret_cast<ComponentCollection<T>*>(shading.get());

	else if (component->GetComponentTypeId() == Transform::ComponentTypeId)
		return reinterpret_cast<ComponentCollection<T>*>(transform.get());

	else
		throwFS("Unknown type used for GetCollectionOfType");
}

template <typename T>
T* ComponentContainer::AddComponent(shared_ptr<T> component, const string& name)
{
	return name == "" ? GetCollectionOfType<T>(component.get())->Add(component) : GetCollectionOfType<T>(component.get())->Add(component, name);
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
	return name == "" ? GetCollectionOfType<T>()->TryGet() : GetCollectionOfType<T>()->TryGet(name);
}

template<typename T>
vector<T*> ComponentContainer::GetComponents() const
{
	return GetCollectionOfType<T>()->GetComponents();
}
