#pragma once
#include "Component.h"

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
	void Add(const shared_ptr<T>& component, const string& name);

};

template <typename T>
void ComponentContainer<T>::Add(const shared_ptr<T>& component, const string& name)
{
	components.emplace(name, component);
}
