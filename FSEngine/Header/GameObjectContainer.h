#pragma once
#include "Systems.h"
#include "Components.h"
#include "GameObject.h"
#include "GameObjectMapper.h"

class GameObjectContainer
{
private:
	Systems* systems = nullptr;
	Components* components = nullptr;

	unique_ptr<GameObjectMapper> gameObjectMapper;
	vector<unique_ptr<GameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);
	GameObject* TryGetGameObjectAtIndex(int index) const;

	void ReMapGameObjectNames(int startIndex);

public:
	GameObjectContainer(Systems* systems, Components* components);

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;
	template <typename T> T* GetGameObjectAs(const string& name) const;

	const vector<unique_ptr<GameObject>>& GetGameObjects() const;
};

template <typename T> T* GameObjectContainer::GetGameObjectAs(const string& name) const
{
	return dynamic_cast<T*>(GetGameObject(name));
}
