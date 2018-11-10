#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Color.h"
#include "Texture.h"
#include "Transform.h"
#include "Model.h"
#include "QuadMesh.h"
#include "CubeMesh.h"
#include "FontTexture.h"
#include "Transform2D.h"

using std::make_shared;

namespace ComponentFactory
{
	shared_ptr<Component> MakeComponent(const string& type);
}

class ComponentContainer
{
private:
	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Shading>> shading;
	unique_ptr<ComponentCollection<Transform>> transform;
	unique_ptr<ComponentCollection<Model>> model;

public:
	ComponentContainer();

	template <typename T>
	ComponentCollection<T>* GetCollectionOfType(Types::ComponentType type) const;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");
	template <typename T>
	void RemoveComponent(const string& name = "");
	template <typename T>
	void RemoveComponent(const T* component);

	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;

	template <typename T>
	vector<T*> GetComponents() const;

	vector<Component*> GetAllComponents() const;
};

template<typename T>
ComponentCollection<T>* ComponentContainer::GetCollectionOfType(Types::ComponentType type) const
{
	switch (type)
	{
	case Mesh::ComponentTypeId:
	case QuadMesh::ComponentTypeId:
	case CubeMesh::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(mesh.get());
	
	case Shading::ComponentTypeId:
	case Color::ComponentTypeId:
	case Texture::ComponentTypeId:
	case FontTexture::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(shading.get());

	case Transform::ComponentTypeId:
	case Transform2D::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(transform.get());

	case Model::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(model.get());

	default:
		throwFS("Unknown type used for GetCollectionOfType");
	}
}

template <typename T>
T* ComponentContainer::AddComponent(shared_ptr<T> component, const string& name)
{
	return GetCollectionOfType<T>(component->GetComponentTypeId())->Add(component, name);
}

template <typename T>
void ComponentContainer::RemoveComponent(const string& name)
{
	GetCollectionOfType<T>(T::ComponentTypeId)->Remove(name);
}

template <typename T>
void ComponentContainer::RemoveComponent(const T* component)
{
	GetCollectionOfType<T>(component->GetComponentTypeId())->Remove(component->GetName());
}

template <typename T>
T* ComponentContainer::GetComponent(const string& name) const
{
	return GetCollectionOfType<T>(T::ComponentTypeId)->Get(name);
}

template <typename T>
T* ComponentContainer::TryGetComponent(const string& name) const
{
	return GetCollectionOfType<T>(T::ComponentTypeId)->TryGet(name);
}

template <typename T>
vector<T*> ComponentContainer::GetComponents() const
{
	return GetCollectionOfType<T>(T::ComponentTypeId)->GetComponents();
}
