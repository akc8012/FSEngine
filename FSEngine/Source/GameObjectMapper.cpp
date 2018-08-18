#include "../Header/GameObjectMapper.h"

void GameObjectMapper::MapGameObject(const string& name, int index)
{
	HandleDuplicateIndex(index);

	auto result = gameObjectMap.emplace(name, index);
	if (!result.second)
		throw "Mapped GameObject with name " + name + " already exists";
}

void GameObjectMapper::HandleDuplicateIndex(int index) const
{
	for (const auto& gameObject : gameObjectMap)
	{
		if (gameObject.second == index)
			throw (string)"Attempted to place duplicate index " + std::to_string(index) + (string)"into GameObjectMap";
	}
}

void GameObjectMapper::UnMapGameObject(const string& name)
{
	try
	{
		gameObjectMap.at(name);
	}
	catch (std::out_of_range)
	{
		throw "Could not find GameObject to unmap with name " + name;
	}

	gameObjectMap.erase(name);
}

int GameObjectMapper::TryGetGameObjectIndex(const string& name) const
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
