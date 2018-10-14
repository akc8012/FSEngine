#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "CubePrimitive.h"
#include "QuadPrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"
#include "Camera.h"
#include "GameObjectContainer.h"

class Scene
{
private:
	string name;
	unique_ptr<GameObjectContainer> gameObjectContainer;

	Systems* systems = nullptr;
	Window* window = nullptr;

	void AddGameObjects();
	string GetFileName() const;

public:
	Scene(const string& name, Systems* systems);
	~Scene();

	void LoadScene();
	void SaveScene() const;

	GameObjectContainer* GetGameObjectContainer() const;
};
