#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems, Window* window)
{
	this->systems = systems;
	this->window = window;

	gameObjectContainer = make_unique<GameObject::GameObjectContainer>(systems);
	AddGameObjects(window);
}

void SceneManager::AddGameObjects(Window* window)
{
	auto gameObject = gameObjectContainer->AddGameObject("Cube", new CubePrimitive(make_shared<ShadingComponent>(0.f, 0.2f, 0.7f)));
	gameObject->GetComponent<ShadingComponent>()->SetFromJson(json::parse(FileSystem::LoadTextFromFile("Resource/Json/scene.json")));

	auto s = gameObject->GetComponent<ShadingComponent>()->GetJson().dump(2);
	FileSystem::WriteTextToFile(s, "Resource/Json/scene.json");
	printFS(s);

	gameObject = gameObjectContainer->AddGameObject("Camera", new Camera(window));
}

GameObject::GameObjectContainer* SceneManager::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}

void SceneManager::Update()
{
	UpdateGameObjects(false);
	UpdateGameObjects(true);
}

void SceneManager::UpdateGameObjects(bool doLateUpdate)
{
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
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
	for (auto& gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoDraw) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject.get());
	}
}
