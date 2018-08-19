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

void SceneManager::UpdateGameObjects(float deltaTime, bool doLateUpdate)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetParameter(GameObject::DoUpdate) && gameObject->GetParameter(GameObject::DoLateUpdate) == doLateUpdate)
			gameObject->Update(deltaTime);
	}
}

void SceneManager::Draw(Renderer* renderer)
{
	DrawGameObjects(renderer, false);
	DrawGameObjects(renderer, true);
}

void SceneManager::DrawGameObjects(Renderer* renderer, bool doLateDraw)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetParameter(GameObject::DoDraw) && gameObject->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject);
	}
}

SceneManager::~SceneManager()
{
	delete gameObjectContainer;
}
