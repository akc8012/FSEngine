#include "../Header/SceneManager.h"

SceneManager::SceneManager()
{
	gameObjectContainer = new GameObject::GameObjectContainer();
}

GameObject::GameObjectContainer* SceneManager::GetGameObjectContainer() const
{
	return gameObjectContainer;
}

void SceneManager::Initialize(FileSystem* fileSystem, Input* input)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		gameObject->SetSystems(gameObjectContainer, fileSystem, input);
		gameObject->Start();
	}
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
		if (gameObject->GetLateRefresh() == refreshLateGameObjects)
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
		if (gameObject->GetLateRefresh() == refreshLateGameObjects)
			renderer->RenderGameObject(gameObject);
	}
}

SceneManager::~SceneManager()
{
	delete gameObjectContainer;
}
