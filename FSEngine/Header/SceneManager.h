#pragma once
#include "IEventListener.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneEditor.h"

class SceneManager : public IEventListener
{
private:
	Systems* systems = nullptr;

	unique_ptr<Scene> currentScene;
	unique_ptr<SceneEditor> sceneEditor;

	void UpdateGameObjects(bool doLateUpdate);
	void DrawGameObjects(Renderer* renderer, bool doLateDraw);

public:
	SceneManager(Systems* systems);
	~SceneManager();

	void Update();
	void Draw(Renderer* renderer);

	void ReceiveEvent(const string& key, const json& event) override;

	Scene* GetCurrentScene() const;
};
