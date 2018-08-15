#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"
#include "GameObject.h"
#include "Renderer.h"

#include <string>
#include <map>
using std::string;
using std::map;

class SceneManager
{
private:
	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	Window* window = nullptr;

	map<string, GameObject*> gameObjects;

	void UpdateGameObjects(float deltaTime, bool refreshLateGameObjects);
	void DrawGameObjects(Renderer* renderer, bool refreshLateGameObjects);

public:
	SceneManager(FileSystem* fileSystem, Input* input, Window* window);
	~SceneManager();

	GameObject* AddGameObject(const string& name, GameObject* gameObject, bool lateRefresh = false);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;

	void Update(float deltaTime);
	void Draw(Renderer* renderer);
};
