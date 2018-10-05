#include "../Header/GameObjectContainer.h"

GameObjectContainer::GameObjectContainer(Systems* systems, Components* components)
{
	this->systems = systems;
	this->components = components;
}

GameObject* GameObjectContainer::AddGameObject(const string& name, GameObject* gameObject)
{
	auto result = gameObjects.emplace(name, gameObject);
	if (!result.second)
		throwFS("GameObject with name " + name + " already exists");

	InitializeGameObject(gameObject, name);
	return gameObject;
}

void GameObjectContainer::InitializeGameObject(GameObject* gameObject, const string& name)
{
	gameObject->SetReferences(systems, components);
	gameObject->SetName(name);
	gameObject->Start();
}

void GameObjectContainer::RemoveGameObject(const string& name)
{
	GameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not find GameObject to remove with name: " + name);

	gameObjects.erase(name);
}

GameObject* GameObjectContainer::GetGameObject(const string& name) const
{
	GameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not get GameObject with name: " + name);

	return gameObject;
}

GameObject* GameObjectContainer::TryGetGameObject(const string& name) const
{
	try
	{
		return gameObjects.at(name).get();
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}

vector<GameObject*> GameObjectContainer::GetGameObjects() const
{
	vector<GameObject*> gameObjectVector;

	for (const auto& gameObject : gameObjects)
		gameObjectVector.push_back(gameObject.second.get());

	return gameObjectVector;
}
