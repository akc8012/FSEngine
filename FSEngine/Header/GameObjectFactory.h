#pragma once
#include "GameObject.h"
#include "CubePrimitive.h"
#include "Camera.h"
#include "RenderText.h"
#include "PlayerShip.h"
#include "QuadPrimitive.h"

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
