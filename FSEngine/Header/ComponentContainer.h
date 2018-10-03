#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "FSException.h"

#include <map>
#include <utility>
#include <memory>
using std::map;
using std::pair;
using std::make_pair;
using std::shared_ptr;

template <typename T>
class ComponentContainer
{
private:
	map<pair<string, string>, shared_ptr<T>> components;

public:
	const shared_ptr<T>& Add(const string& key, const shared_ptr<T>& component, const string& name = Types::ComponentTypeString[T::ComponentTypeId]);
	shared_ptr<T> Get(const string& key, const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
	shared_ptr<T> TryGet(const string& key, const string& name = Types::ComponentTypeString[T::ComponentTypeId]) const;
};

template <typename T>
const shared_ptr<T>& ComponentContainer<T>::Add(const string& key, const shared_ptr<T>& component, const string& name)
{
	auto result = components.emplace(make_pair(key, name), component);
	if (!result.second)
		throwFS("Component with name \"" + name + "\" already exists");

	return component;
}

template <typename T>
shared_ptr<T> ComponentContainer<T>::Get(const string& key, const string& name) const
{
	auto component = TryGet(key, name);
	if (component == nullptr)
		throwFS("Could not find component on key \"" + key + "\" with name \"" + name + "\"");

	return component;
}

template <typename T>
shared_ptr<T> ComponentContainer<T>::TryGet(const string& key, const string& name) const
{
	try
	{
		return components.at(make_pair(key, name));
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}
