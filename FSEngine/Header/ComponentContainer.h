#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "FSException.h"

#include <unordered_map>
#include <memory>
using std::unordered_map;
using std::shared_ptr;

template <typename T>
class ComponentContainer
{
private:
	unordered_map<string, shared_ptr<T>> components;

public:
	const shared_ptr<T>& Add(const shared_ptr<T>& component, const string& name = Types::ComponentTypeString[T::ComponentTypeId]);

};

template <typename T>
const shared_ptr<T>& ComponentContainer<T>::Add(const shared_ptr<T>& component, const string& name)
{
	auto result = components.emplace(name, component);
	if (!result.second)
		throwFS("Component with name \"" + name + "\" already exists");

	return component;
}
