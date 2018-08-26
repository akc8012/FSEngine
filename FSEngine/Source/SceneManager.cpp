#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems, Window* window)
{
	gameObjectContainer = new GameObject::GameObjectContainer(systems);
	AddGameObjects(window);
}

void SceneManager::AddGameObjects(Window* window)
{
	GameObject* memeFaceCube = GetGameObjectContainer()->AddGameObject("MemeFaceCube", new CubePrimitive(new TextureComponent("Resource/Image/awesomeface.png")));
	memeFaceCube->GetComponent<TransformComponent>()->SetPosition(4.5f, 0.2f, 0);

	GameObject* greenCube = GetGameObjectContainer()->AddGameObject("GreenCube", new CubePrimitive(new ShadingComponent(0.1f, 0.6f, 0.3f)));
	greenCube->GetComponent<TransformComponent>()->SetPosition(6, -0.2f, 0.1f);
	greenCube->GetComponent<TransformComponent>()->SetScale(2, 0.8f, 2.8f);

	GetGameObjectContainer()->AddGameObject("1", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(0, 1, 3);
	GetGameObjectContainer()->AddGameObject("2", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(1, -1, -1);
	GetGameObjectContainer()->AddGameObject("3", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(-0.8f, 0, -2);
	GetGameObjectContainer()->AddGameObject("4", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(-2, -1, 0);

	//for (int i = 5; i < 100; i++)
	//	GetGameObjectContainer()->AddGameObject(std::to_string(i), new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition((float)i, 0, (float)i);

	RenderText* debugText = dynamic_cast<RenderText*>(GetGameObjectContainer()->AddGameObject("DebugText", new RenderText()));
	debugText->SetWindow(window);
	debugText->GetParameterCollection()->SetParameter(GameObject::DoLateDraw, true);
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	GetGameObjectContainer()->AddGameObject("Camera", new Camera(window));
	GetGameObjectContainer()->AddGameObject("PlayerShip", new PlayerShip());
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
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoUpdate) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateUpdate) == doLateUpdate)
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
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoDraw) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject);
	}
}

SceneManager::~SceneManager()
{
	delete gameObjectContainer;
}
