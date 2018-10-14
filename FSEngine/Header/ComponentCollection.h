#pragma once
#include "KeyNamePair.h"
#include "Component.h"
#include "ComponentType.h"
#include "FSException.h"

#include <unordered_map>
#include <vector>
#include <utility>
#include <memory>
using std::unordered_map;
using std::vector;
using std::shared_ptr;
using std::move;

template <typename T>
class ComponentCollection
{
private:
	unordered_map<KeyNamePair, shared_ptr<T>> components;

public:
	T* Add(const string& key, shared_ptr<T> component, const string& name = Types::ComponentTypeString[T::ComponentTypeId]);
	// Remove();

	T* Get(const string& key, const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
	T* TryGet(const string& key, const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;

	vector<T*> GetComponents(const string& key) const;
};

template <typename T>
T* ComponentCollection<T>::Add(const string& key, shared_ptr<T> component, const string& name)
{
	auto result = components.emplace(KeyNamePair(key, name), move(component));
	if (!result.second)
		throwFS("Component with name \"" + name + "\" already exists");

	auto emplacedComponent = result.first->second.get();
	emplacedComponent->SetName(name);
	return emplacedComponent;
}

template <typename T>
T* ComponentCollection<T>::Get(const string& key, const string& name) const
{
	auto component = TryGet(key, name);
	if (component == nullptr)
		throwFS("Could not find component on key \"" + key + "\" with name \"" + name + "\"");

	return component;
}

template <typename T>
T* ComponentCollection<T>::TryGet(const string& key, const string& name) const
{
	try
	{
		return components.at(KeyNamePair(key, name)).get();
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}

template <typename T>
vector<T*> ComponentCollection<T>::GetComponents(const string& key) const
{
	vector<T*> componentsWithKey;

	for (const auto& component : components)
	{
		if (component.first.key == key)
			componentsWithKey.push_back(component.second.get());
	}

	return componentsWithKey;
}
