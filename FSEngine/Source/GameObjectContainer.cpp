#include "../Header/GameObjectContainer.h"

GameObjectContainer::GameObjectContainer(Systems* systems, Components* components)
{
	this->systems = systems;
	this->components = components;
	gameObjectMapper = make_unique<GameObjectMapper>();
}

GameObject* GameObjectContainer::AddGameObject(const string& name, GameObject* gameObject)
{
	int index = (int)gameObjects.size();
	gameObjectMapper->MapGameObject(name, index);

	gameObjects.push_back(unique_ptr<GameObject>(gameObject));
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
	int index = gameObjectMapper->UnMapGameObject(name);
	gameObjects.erase(gameObjects.begin() + index);

	ReMapGameObjectNames(index);
}

void GameObjectContainer::ReMapGameObjectNames(int startIndex)
{
	for (int index = startIndex; index < gameObjects.size(); index++)
	{
		string name = gameObjects[index]->GetName();
		gameObjectMapper->ReMapGameObject(name, index);
	}
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
	int index = gameObjectMapper->TryGetGameObjectIndex(name);
	return TryGetGameObjectAtIndex(index);
}

GameObject* GameObjectContainer::TryGetGameObjectAtIndex(int index) const
{
	try
	{
		return gameObjects.at(index).get();
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}

const vector<unique_ptr<GameObject>>& GameObjectContainer::GetGameObjects() const
{
	return gameObjects;
}
