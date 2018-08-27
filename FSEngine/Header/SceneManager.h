#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Window.h"
#include "CubePrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class SceneManager
{
private:
	GameObject::GameObjectContainer* gameObjectContainer = nullptr;

	void AddGameObjects(Window* window);
	void UpdateGameObjects(bool doLateUpdate);
	void DrawGameObjects(Renderer* renderer, bool doLateDraw);

public:
	SceneManager(Systems* systems, Window* window);
	~SceneManager();

	GameObject::GameObjectContainer* GetGameObjectContainer() const;

	void Update();
	void Draw(Renderer* renderer);
};
