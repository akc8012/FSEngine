#include "../Header/GameObjectMapper.h"

void GameObjectMapper::MapGameObject(const string& name, int index)
{
	auto result = gameObjectMap.emplace(name, index);
	if (!result.second)
		throwFS("Mapped GameObject with name " + name + " already exists");
}

int GameObjectMapper::UnMapGameObject(const string& name)
{
	int index = TryGetGameObjectIndex(name);
	if (index == -1)
		throwFS("Could not find GameObject to UnMap with name: " + name);

	gameObjectMap.erase(name);
	return index;
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

void GameObjectMapper::Clear()
{
	gameObjectMap.clear();
}
