#pragma once
#include "GameObjectMapper.h"
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"
#include "GameObject.h"
#include "Renderer.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class SceneManager
{
private:
	GameObjectMapper* gameObjectMapper = nullptr;

	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	Window* window = nullptr;

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
