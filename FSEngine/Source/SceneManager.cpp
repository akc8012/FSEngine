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
	gameObject->GetComponent<TransformComponent>()->SetPosition(0, 1, -4);
	gameObject->GetComponent<TransformComponent>()->SetScale(vec3(1, 2, 0.5f));

	json j;
	j["Position"] = { -1, 0, -1 };
	j["EulerAngles"] = { 0, 0, 0 };
	j["Scale"] = { 12, 1, 1 };
	gameObject->GetComponent<TransformComponent>()->SetFromJson(j);

	auto s = gameObject->GetComponent<TransformComponent>()->GetJson().dump(2);
	printFS(s);

	gameObjectContainer->AddGameObject("Camera", new Camera(window));
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
