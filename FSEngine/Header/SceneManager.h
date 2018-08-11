#pragma once
#include "GameObject.h"
#include "Renderer.h"

#include <string>
#include <map>
using std::string;
using std::map;

class SceneManager
{
private:
	map<string, GameObject*> gameObjects;

public:
	~SceneManager();

	void AddGameObject(const string& name, GameObject* gameObject);
	GameObject* GetGameObject(const string& name) const;

	void Update(float deltaTime);
	void Draw(Renderer* renderer);
};
