#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

class SceneManager
{
private:
	unique_ptr<Scene> currentScene;

	void UpdateGameObjects(bool doLateUpdate);
	void DrawGameObjects(Renderer* renderer, bool doLateDraw);

public:
	SceneManager(Systems* systems);

	void Update();
	void Draw(Renderer* renderer);

	Scene* GetCurrentScene() const;
};
