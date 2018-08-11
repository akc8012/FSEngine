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

public:
	SceneManager(FileSystem* fileSystem, Input* input, Window* window);
	~SceneManager();

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	GameObject* GetGameObject(const string& name) const;

	void Update(float deltaTime);
	void Draw(Renderer* renderer);
};
