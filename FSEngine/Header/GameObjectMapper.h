#pragma once
#include "FSException.h"

#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class GameObjectMapper
{
private:
	unordered_map<string, int> gameObjectMap;

public:
	void MapGameObject(const string& name, int index);
	void ReMapGameObject(const string& name, int index);
	int UnMapGameObject(const string& name);

	int TryGetGameObjectIndex(const string& name) const;
};
