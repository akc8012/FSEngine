#pragma once
#include "IEventListener.h"
#include "GameObjectFactory.h"
#include "GameObjectContainer.h"
#include "Renderer.h"

class Scene : public IEventListener
{
private:
	string name;
	unique_ptr<GameObjectContainer> gameObjectContainer;

	Systems* systems = nullptr;
	Window* window = nullptr;

	vector<string> LoadGameObjectsFromJson(const json& j);
	json TryParseSceneJson() const;
	bool SceneLoaded() const;

	void RemoveUnloadedGameObjects(const vector<string>& loadedGameObjectNames);
	bool GameObjectIsLoaded(const string& name, const vector<string>& loadedGameObjectNames);
	void SendSceneLoadedEvents();

	void AddGameObjects();

	string GetFileName() const;

public:
	Scene(const string& name, Systems* systems);

	void LoadScene();
	void SaveScene() const;
	
	void ReceiveEvent(const string& key, const json& event) override;

	GameObjectContainer* GetGameObjectContainer() const;
};
