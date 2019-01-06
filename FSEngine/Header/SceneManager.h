#pragma once
#include "IEventListener.h"
#include "IUpdatable.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneEditor.h"

class SceneManager : public IEventListener, public IUpdatable
{
private:
	Systems* systems = nullptr;

	unique_ptr<Scene> currentScene;
	unique_ptr<SceneEditor> sceneEditor;

	void UpdateGameObjects(bool doLateUpdate);
	void DrawGameObjects(Renderer* renderer, bool doLateDraw);

	void DrawImGuiGameObjectsWindow() const;
	vector<const char*> GetGameObjectNameList() const;

public:
	SceneManager(Systems* systems);
	~SceneManager();

	void Update() override;
	void Draw(Renderer* renderer);

	void ReceiveEvent(const string& key, const json& event) override;

	Scene* GetCurrentScene() const;
};
