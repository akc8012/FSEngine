#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems)
{
	gameObjectContainer = new GameObject::GameObjectContainer(systems);
}

GameObject::GameObjectContainer* SceneManager::GetGameObjectContainer() const
{
	return gameObjectContainer;
}

void SceneManager::Update(float deltaTime)
{
	UpdateGameObjects(deltaTime, false);
	UpdateGameObjects(deltaTime, true);
}

void SceneManager::UpdateGameObjects(float deltaTime, bool refreshLateGameObjects)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->IsLateRefresh() == refreshLateGameObjects)
			gameObject->Update(deltaTime);
	}
}

void SceneManager::Draw(Renderer* renderer)
{
	DrawGameObjects(renderer, false);
	DrawGameObjects(renderer, true);
}

void SceneManager::DrawGameObjects(Renderer* renderer, bool refreshLateGameObjects)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->IsLateRefresh() == refreshLateGameObjects)
			renderer->RenderGameObject(gameObject);
	}
}

SceneManager::~SceneManager()
{
	delete gameObjectContainer;
}
