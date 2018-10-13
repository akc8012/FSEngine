#pragma once
#include "GameObject.h"
#include "Components.h"
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
	Systems* systems = nullptr;
	Window* window = nullptr;

	unique_ptr<Components> components;
	unique_ptr<GameObjectContainer> gameObjectContainer;

	void AddGameObjects();
	string GetFileName() const;

public:
	Scene(const string& name, Systems* systems);
	~Scene();

	void LoadScene();
	void SaveScene() const;

	GameObjectContainer* GetGameObjectContainer() const;
	Components* GetComponents() const;
};
