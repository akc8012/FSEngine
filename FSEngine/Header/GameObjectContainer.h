#pragma once
#include "GameObject.h"

class GameObject::GameObjectContainer
{
private:
	GameObjectMapper* gameObjectMapper = nullptr;
	vector<GameObject*> gameObjects;

public:
	GameObjectContainer();
	~GameObjectContainer();

	GameObject* AddGameObject(const string& name, GameObject* gameObject);

	GameObject* GetGameObject(const string& name) const;
	GameObject* GetGameObjectAtIndex(int index) const;
	vector<GameObject*> GetGameObjects() const;
};
