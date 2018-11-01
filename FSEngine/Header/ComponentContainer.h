#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Color.h"
#include "Texture.h"
#include "Transform.h"
#include "Model.h"
#include "QuadMesh.h"
#include "FontTexture.h"

using std::make_shared;

namespace ComponentFactory
{
	shared_ptr<Component> MakeComponent(const string& type);
}

class ComponentContainer
{
private:
	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Color>> color;
	unique_ptr<ComponentCollection<Texture>> texture;
	unique_ptr<ComponentCollection<Transform>> transform;
	unique_ptr<ComponentCollection<Model>> model;

public:
	ComponentContainer();

	template <typename T>
	ComponentCollection<T>* GetCollectionOfType(Types::ComponentType type) const;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");

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
		return reinterpret_cast<ComponentCollection<T>*>(mesh.get());

	case Color::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(color.get());

	case Texture::ComponentTypeId:
	case FontTexture::ComponentTypeId:
		return reinterpret_cast<ComponentCollection<T>*>(texture.get());

	case Transform::ComponentTypeId:
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
