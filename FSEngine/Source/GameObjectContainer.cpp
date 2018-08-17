#include "../Header/GameObjectContainer.h"

void GameObjectContainer::MapGameObject(const string& name, int index)
{
	HandleDuplicateIndex(index);

	auto result = gameObjectMap.emplace(name, index);
	if (!result.second)
		throw "Mapped game object name with name " + name + " already exists";
}

void GameObjectContainer::HandleDuplicateIndex(int index) const
{
	for (const auto& gameObject : gameObjectMap)
	{
		if (gameObject.second == index)
			throw (string)"Attempted to place duplicate index " + std::to_string(index) + (string)"into GameObjectMap";
	}
}

void GameObjectContainer::UnMapGameObject(const string& name)
{
	try
	{
		gameObjectMap.at(name);
	}
	catch (std::out_of_range)
	{
		throw "Could not find game object to unmap with name " + name;
	}

	gameObjectMap.erase(name);
}

int GameObjectContainer::GetGameObjectIndex(const string& name) const
{
	int index = TryGetGameObjectIndex(name);
	if (index == -1)
		throw "Could not find GameObject index with name: " + name;

	return index;
}

int GameObjectContainer::TryGetGameObjectIndex(const string& name) const
{
	try
	{
		return gameObjectMap.at(name);
	}
	catch (std::out_of_range)
	{
		return -1;
	}
}

GameObject* GameObjectContainer::GetGameObjectAtIndex(int index)
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
