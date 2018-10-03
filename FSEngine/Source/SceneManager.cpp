#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems, Window* window)
{
	currentScene = make_unique<Scene>("scene", systems, window);
}

void SceneManager::Update()
{
	UpdateGameObjects(false);
	UpdateGameObjects(true);
}

void SceneManager::UpdateGameObjects(bool doLateUpdate)
{
	for (auto& gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoUpdate) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateUpdate) == doLateUpdate)
			gameObject->Update();
	}
}

void SceneManager::Draw(Renderer* renderer)
{
	DrawGameObjects(renderer, false);
	DrawGameObjects(renderer, true);
}

void SceneManager::DrawGameObjects(Renderer* renderer, bool doLateDraw)
{
	for (auto& gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoDraw) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject->GetName());
	}
}

Scene* SceneManager::GetCurrentScene() const
{
	return currentScene.get();
}
