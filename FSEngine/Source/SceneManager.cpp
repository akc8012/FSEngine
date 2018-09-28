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
	GameObject* gameObject = nullptr;

	gameObject = gameObjectContainer->AddGameObject("MemeFaceCube", new CubePrimitive(make_shared<Texture>("Resource/Image/awesomeface.png")));
	gameObject->GetComponent<TransformComponent>()->SetPosition(4.5f, 0.2f, 0);

	gameObject = gameObjectContainer->AddGameObject("GreenCube", new CubePrimitive(make_shared<Shading>(0.1f, 0.6f, 0.3f)));
	gameObject->GetComponent<TransformComponent>()->SetPosition(6, -0.2f, 0.1f);
	gameObject->GetComponent<TransformComponent>()->SetScale(2, 0.8f, 2.8f);

	gameObject = gameObjectContainer->AddGameObject("Red", new CubePrimitive(make_shared<Shading>(0.8f, 0.f, 0.f)));
	gameObject->GetComponent<TransformComponent>()->SetPosition(1.5f, 1, -3);

	gameObject = gameObjectContainer->AddGameObject("Green", new CubePrimitive(make_shared<Shading>(0.f, 0.8f, 0.f)));
	gameObject->GetComponent<TransformComponent>()->SetPosition(1, -1, -1);

	gameObject = gameObjectContainer->AddGameObject("Blue", new CubePrimitive(make_shared<Shading>(0.f, 0.f, 0.8f)));
	gameObject->GetComponent<TransformComponent>()->SetPosition(-0.8f, 0, -2);

	gameObject = gameObjectContainer->AddGameObject("Yellow", new CubePrimitive(make_shared<Shading>(0.6f, 0.6f, 0.f)));
	gameObject->GetComponent<TransformComponent>()->SetPosition(-2, -1, 0);

	for (int i = 0; i < 100; i++)
	{
		GameObject* cube = new CubePrimitive(make_shared<Shading>(systems->random->GetRandomUniformVector(0.f, 1.f)));
		gameObject = gameObjectContainer->AddGameObject(std::to_string(i), cube);
		gameObject->GetComponent<TransformComponent>()->SetPosition(systems->random->GetRandomUniformVector(-20.f, 20.f));
	}

	gameObjectContainer->AddGameObject("DebugText", new RenderText(window));
	RenderText* debugText = gameObjectContainer->GetGameObjectAs<RenderText>("DebugText");
	debugText->SetText("Debug text");
	debugText->GetParameterCollection()->SetParameter(GameObject::DoLateUpdate, true);
	debugText->GetParameterCollection()->SetParameter(GameObject::DoLateDraw, true);
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	gameObjectContainer->AddGameObject("Camera", new Camera(window));
	gameObjectContainer->AddGameObject("PlayerShip", new PlayerShip());
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
