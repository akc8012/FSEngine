#pragma once
#include "GameObject.h"
#include "Renderer.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class SceneManager
{
private:
	GameObject::GameObjectContainer* gameObjectContainer = nullptr;

	void UpdateGameObjects(float deltaTime, bool refreshLateGameObjects);
	void DrawGameObjects(Renderer* renderer, bool refreshLateGameObjects);

public:
	SceneManager(Systems* systems);
	~SceneManager();

	GameObject::GameObjectContainer* GetGameObjectContainer() const;

	void Update(float deltaTime);
	void Draw(Renderer* renderer);
};
