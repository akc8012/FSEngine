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

	string GetName(const string& name) const;

public:
	T* Add(shared_ptr<T> component, const string& name);
	// Remove();

	T* Get(const string& name) const;
	T* TryGet(const string& name) const;

	vector<T*> GetComponents() const;
};

template <typename T>
T* ComponentCollection<T>::Add(shared_ptr<T> component, const string& name)
{
	auto result = components.emplace(GetName(name), move(component));
	if (!result.second)
		throwFS("Component with name \"" + name + "\" already exists");

	auto emplacedComponent = result.first->second.get();
	emplacedComponent->SetName(GetName(name));
	return emplacedComponent;
}

template <typename T>
T* ComponentCollection<T>::Get(const string& name) const
{
	auto component = TryGet(GetName(name));
	if (component == nullptr)
		throwFS("Could not find component with name \"" + GetName(name) + "\"");

	return component;
}

template <typename T>
T* ComponentCollection<T>::TryGet(const string& name) const
{
	auto component = components.find(GetName(name));
	if (component != components.end())
		return component->second.get();

	return nullptr;
}

template <typename T>
string ComponentCollection<T>::GetName(const string& name) const
{
	return name == "" ? Types::ComponentTypeString[T::ComponentTypeId] : name;
}

template <typename T>
vector<T*> ComponentCollection<T>::GetComponents() const
{
	vector<T*> componentVector;

	for (const auto& component : components)
		componentVector.push_back(component.second.get());

	return componentVector;
}
