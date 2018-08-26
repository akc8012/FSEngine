#include "../Header/GameObjectMapper.h"

const string& GameObjectMapper::MapGameObject(const string& name, int index)
{
	HandleDuplicateIndex(index);

	auto result = gameObjectMap.emplace(name, index);
	if (!result.second)
		throwFS("Mapped GameObject with name " + name + " already exists");

	return result.first->first;
}

void GameObjectMapper::HandleDuplicateIndex(int index) const
{
	for (const auto& gameObject : gameObjectMap)
	{
		if (gameObject.second == index)
			throwFS((string)"Attempted to place duplicate index " + std::to_string(index) + (string)"into GameObjectMap");
	}
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
