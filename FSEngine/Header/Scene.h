#pragma once
#include "IEventListener.h"
#include "GameObject.h"
#include "Renderer.h"
#include "CubePrimitive.h"
#include "QuadPrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"
#include "Camera.h"
#include "GameObjectContainer.h"
#include "GameObjectFactory.h"

class Scene : public IEventListener
{
private:
	string name;
	unique_ptr<GameObjectContainer> gameObjectContainer;

	Systems* systems = nullptr;
	Window* window = nullptr;

	void AddGameObjects();
	string GetFileName() const;

public:
	Scene(const string& name, Systems* systems);
	~Scene();

	void LoadScene();
	void SaveScene() const;
	
	void ReceiveEvent(const string& key, const json& event) override;

	GameObjectContainer* GetGameObjectContainer() const;
};
