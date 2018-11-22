#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems)
 : systems(systems)
{
	currentScene = make_unique<Scene>("scene", systems);
	sceneEditor = make_unique<SceneEditor>(currentScene.get(), systems);

	systems->eventSystem->AddListener("SaveKeyPressed", this);
	systems->eventSystem->AddListener("LoadKeyPressed", this);
	systems->eventSystem->AddListener("GameStopped", this);
	systems->eventSystem->AddListener("WindowFocusGained", this);
	systems->eventSystem->AddListener("WindowFocusLost", this);
}

void SceneManager::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SaveKeyPressed" || key == "GameStopped" ||
		(key == "WindowFocusLost" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus")))
		currentScene->SaveScene();

	if (key == "LoadKeyPressed" || (key == "WindowFocusGained" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus")))
	{
		currentScene->LoadScene();
		sceneEditor->InitializeEditor();
	}
}

void SceneManager::Update()
{
	sceneEditor->Update();

	UpdateGameObjects(false);
	UpdateGameObjects(true);
}

void SceneManager::UpdateGameObjects(bool doLateUpdate)
{
	for (auto gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
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
	for (auto gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoDraw) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject);
	}
}

Scene* SceneManager::GetCurrentScene() const
{
	return currentScene.get();
}

SceneManager::~SceneManager()
{
	systems->eventSystem->RemoveListener(this);
}
