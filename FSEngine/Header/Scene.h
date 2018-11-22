#pragma once
#include "GameObjectFactory.h"
#include "GameObjectContainer.h"
#include "Renderer.h"

class Scene
{
private:
	string name;
	unique_ptr<GameObjectContainer> gameObjectContainer;

	Systems* systems = nullptr;
	Window* window = nullptr;

	json TryParseSceneJson() const;
	bool SceneLoaded() const;

	void RemoveUnloadedGameObjects(const json& sceneJson);
	void LoadGameObjectsFromJson(const json& j);
	void SendSceneLoadedEvents();

	string GetFileName() const;

public:
	Scene(const string& name, Systems* systems);

	void LoadScene();
	void SaveScene() const;

	GameObjectContainer* GetGameObjectContainer() const;
};
