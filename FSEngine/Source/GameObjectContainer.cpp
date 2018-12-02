#include "../Header/GameObjectContainer.h"

GameObjectContainer::GameObjectContainer(Systems* systems)
 : systems(systems)
{

}

IGameObject* GameObjectContainer::AddGameObject(const string& name, unique_ptr<IGameObject> gameObject)
{
	auto result = gameObjects.emplace(name, move(gameObject));
	if (!result.second)
		throwFS("GameObject with name " + name + " already exists");

	IGameObject* emplacedGameObject = result.first->second.get();
	InitializeGameObject(static_cast<GameObject*>(emplacedGameObject), name);
	systems->eventSystem->SendEvent("GameObjectAdded", name, false);

	return emplacedGameObject;
}

void GameObjectContainer::InitializeGameObject(GameObject* gameObject, const string& name)
{
	gameObject->SetReferences(systems, this);
	gameObject->SetName(name);
	gameObject->Start();
}

void GameObjectContainer::RemoveGameObject(string name)
{
	IGameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not find GameObject to remove with name: " + name);

	gameObjects.erase(name);
	systems->eventSystem->SendEvent("GameObjectRemoved", name);
}

IGameObject* GameObjectContainer::GetGameObject(const string& name) const
{
	IGameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not get GameObject with name: " + name);

	return gameObject;
}

IGameObject* GameObjectContainer::TryGetGameObject(const string& name) const
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

vector<IGameObject*> GameObjectContainer::GetGameObjects() const
{
	vector<IGameObject*> gameObjectVector;

	for (const auto& gameObject : gameObjects)
		gameObjectVector.push_back(gameObject.second.get());

	return gameObjectVector;
}

int GameObjectContainer::GetGameObjectCount() const
{
	return (int)gameObjects.size();
}
