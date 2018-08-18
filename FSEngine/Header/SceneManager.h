#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"

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
	SceneManager();
	~SceneManager();

	GameObject::GameObjectContainer* GetGameObjectContainer() const;

	void Initialize(FileSystem* fileSystem, Input* input, Window* window);
	void Update(float deltaTime);
	void Draw(Renderer* renderer);
};
