#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class GameObjectContainer
{
private:
	unordered_map<string, int> gameObjectMap;

	void HandleDuplicateIndex(int index) const;

public:
	void MapGameObject(const string& name, int index);
	void UnMapGameObject(const string& name);

	int GetGameObjectIndex(const string& name) const;
	int TryGetGameObjectIndex(const string& name) const;
};
