#include "../Header/GameObject.h"

GameObject::GameObjectContainer::GameObjectContainer(Systems* systems)
{
	this->systems = systems;
	gameObjectMapper = make_unique<GameObjectMapper>();
}

GameObject* GameObject::GameObjectContainer::AddGameObject(const string& name, GameObject* gameObject)
{
	const string& mappedName = gameObjectMapper->MapGameObject(name, (int)gameObjects.size());

	gameObjects.push_back(unique_ptr<GameObject>(gameObject));
	InitializeGameObject(gameObject, mappedName);

	return gameObject;
}

void GameObject::GameObjectContainer::InitializeGameObject(GameObject* gameObject, const string& name)
{
	gameObject->SetSystems(systems, this);
	gameObject->SetName(name);
	gameObject->Start();
}

void GameObject::GameObjectContainer::RemoveGameObject(const string& name)
{
	GameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not remove GameObject with name: " + name);

	int index = gameObjectMapper->UnMapGameObject(name);
	gameObjects.erase(gameObjects.begin() + index);
}

GameObject* GameObject::GameObjectContainer::GetGameObject(const string& name) const
{
	GameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throwFS("Could not get GameObject with name: " + name);

	return gameObject;
}

GameObject* GameObject::GameObjectContainer::TryGetGameObject(const string& name) const
{
	int index = gameObjectMapper->TryGetGameObjectIndex(name);
	return TryGetGameObjectAtIndex(index);
}

GameObject* GameObject::GameObjectContainer::TryGetGameObjectAtIndex(int index) const
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

const vector<unique_ptr<GameObject>>& GameObject::GameObjectContainer::GetGameObjects() const
{
	return gameObjects;
}
