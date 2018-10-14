#pragma once
#include "Systems.h"
#include "ComponentContainer.h"
#include "IGameObject.h"

#include <string>
#include <map>
using std::string;
using std::map;

class GameObjectContainer
{
private:
	Systems* systems = nullptr;
	ComponentContainer* components = nullptr;

	map<string, unique_ptr<IGameObject>> gameObjects;

	void InitializeGameObject(IGameObject* gameObject, const string& name);

public:
	GameObjectContainer(Systems* systems, ComponentContainer* components);

	IGameObject* AddGameObject(const string& name, unique_ptr<IGameObject> gameObject);
	void RemoveGameObject(const string& name);

	IGameObject* GetGameObject(const string& name) const;
	IGameObject* TryGetGameObject(const string& name) const;

	template <typename T>
	T* GetGameObjectAs(const string& name) const;

	vector<IGameObject*> GetGameObjects() const;
};

template <typename T>
T* GameObjectContainer::GetGameObjectAs(const string& name) const
{
	return dynamic_cast<T*>(GetGameObject(name));
}
