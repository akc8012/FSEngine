#include "../Header/GameObjectContainer.h"

GameObject::GameObjectContainer::GameObjectContainer()
{
	gameObjectMapper = new GameObjectMapper();
}

GameObject* GameObject::GameObjectContainer::AddGameObject(const string& name, GameObject* gameObject)
{
	gameObjectMapper->MapGameObject(name, (int)gameObjects.size());
	gameObjects.push_back(gameObject);

	return gameObject;
}

GameObject* GameObject::GameObjectContainer::GetGameObject(const string& name) const
{
	int index = gameObjectMapper->GetGameObjectIndex(name);
	return GetGameObjectAtIndex(index);
}

GameObject* GameObject::GameObjectContainer::GetGameObjectAtIndex(int index) const
{
	try
	{
		return gameObjects.at(index);
	}
	catch (std::out_of_range)
	{
		throw "Could not get game object at index: " + std::to_string(index);
	}
}

vector<GameObject*> GameObject::GameObjectContainer::GetGameObjects() const
{
	return gameObjects;
}

GameObject::GameObjectContainer::~GameObjectContainer()
{
	delete gameObjectMapper;

	for (auto& gameObject : gameObjects)
		delete gameObject;
}
