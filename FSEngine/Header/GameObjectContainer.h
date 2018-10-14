#pragma once
#include "IGameObjectContainer.h"
#include "Systems.h"
#include "GameObject.h"

#include <string>
#include <map>
using std::string;
using std::map;

class GameObjectContainer : public IGameObjectContainer
{
private:
	Systems* systems = nullptr;

	map<string, unique_ptr<IGameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);

public:
	GameObjectContainer(Systems* systems);

	IGameObject* AddGameObject(const string& name, unique_ptr<IGameObject> gameObject);
	void RemoveGameObject(const string& name) override;

	IGameObject* GetGameObject(const string& name) const override;
	IGameObject* TryGetGameObject(const string& name) const override;

	vector<IGameObject*> GetGameObjects() const override;
};
