#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Window.h"
#include "CubePrimitive.h"
#include "QuadPrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class Scene
{
private:
	string name;
	Systems* systems = nullptr;
	Window* window = nullptr;

	unique_ptr<GameObject::GameObjectContainer> gameObjectContainer;

	void AddGameObjects(Window* window);

public:
	Scene(const string& name, Systems* systems, Window* window);

	void SaveScene() const;

	GameObject::GameObjectContainer* GetGameObjectContainer() const;
};
