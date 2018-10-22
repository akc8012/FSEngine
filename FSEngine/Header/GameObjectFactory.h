#pragma once
#include "GameObject.h"
#include "CubePrimitive.h"

#include <string>
#include <memory>
using std::string;
using std::unique_ptr;
using std::make_unique;

class GameObjectFactory
{
public:
	static unique_ptr<GameObject> MakeGameObject(const string& type);

};
