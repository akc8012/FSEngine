#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "FSException.h"

#include <map>
#include <vector>
#include <memory>
using std::map;
using std::vector;
using std::shared_ptr;
using std::move;

template <typename T>
class ComponentCollection
{
private:
	map<string, shared_ptr<T>> components;

public:
	T* Add(shared_ptr<T> component, const string& name = Types::ComponentTypeString[T::ComponentTypeId]);
	// Remove();

	T* Get(const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
	T* TryGet(const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;

	vector<T*> GetComponents() const;
};

template <typename T>
T* ComponentCollection<T>::Add(shared_ptr<T> component, const string& name)
{
	auto result = components.emplace(name, move(component));
	if (!result.second)
		throwFS("Component with name \"" + name + "\" already exists");

	auto emplacedComponent = result.first->second.get();
	emplacedComponent->SetName(name);
	return emplacedComponent;
}

template <typename T>
T* ComponentCollection<T>::Get(const string& name) const
{
	auto component = TryGet(name);
	if (component == nullptr)
		throwFS("Could not find component with name \"" + name + "\"");

	return component;
}

template <typename T>
T* ComponentCollection<T>::TryGet(const string& name) const
{
	try
	{
		return components.at(name).get();
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}

template <typename T>
vector<T*> ComponentCollection<T>::GetComponents() const
{
	vector<T*> componentVector;

	for (const auto& component : components)
		componentVector.push_back(component.second.get());

	return componentVector;
}
