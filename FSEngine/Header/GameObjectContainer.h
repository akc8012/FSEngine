#pragma once
#include "Systems.h"
#include "Components.h"
#include "GameObject.h"

#include <string>
#include <map>
using std::string;
using std::map;

class GameObjectContainer
{
private:
	Systems* systems = nullptr;
	Components* components = nullptr;

	map<string, unique_ptr<GameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);

public:
	GameObjectContainer(Systems* systems, Components* components);

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;

	template <typename T>
	T* GetGameObjectAs(const string& name) const;

	vector<GameObject*> GetGameObjects() const;
};

template <typename T>
T* GameObjectContainer::GetGameObjectAs(const string& name) const
{
	return dynamic_cast<T*>(GetGameObject(name));
}
