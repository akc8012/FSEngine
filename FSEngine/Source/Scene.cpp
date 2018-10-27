#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);

	AddGameObjects();
	LoadScene();

	systems->eventSystem->AddListener("SaveKeyPressed", this);
	systems->eventSystem->AddListener("LoadKeyPressed", this);
}

void Scene::AddGameObjects()
{
	auto gameObject = gameObjectContainer->AddGameObject("MemeFaceCube", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Texture>("Resource/Image/awesomeface.png"));
	gameObject->GetComponent<Transform>()->SetPosition(4.5f, 0.2f, 0);

	gameObject = gameObjectContainer->AddGameObject("GreenCube", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.1f, 0.6f, 0.3f));
	gameObject->GetComponent<Transform>()->SetPosition(6, -0.2f, 0.1f);
	gameObject->GetComponent<Transform>()->SetScale(2, 0.8f, 2.8f);

	gameObject = gameObjectContainer->AddGameObject("Red", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.8f, 0.f, 0.f));
	gameObject->GetComponent<Transform>()->SetPosition(1.5f, 1, -3);

	gameObject = gameObjectContainer->AddGameObject("Green", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.f, 0.8f, 0.f));
	gameObject->GetComponent<Transform>()->SetPosition(1, -1, -1);

	gameObject = gameObjectContainer->AddGameObject("Blue", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.f, 0.f, 0.8f));
	gameObject->GetComponent<Transform>()->SetPosition(-0.8f, 0, -2);

	gameObject = gameObjectContainer->AddGameObject("Yellow", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.6f, 0.6f, 0.f));
	gameObject->GetComponent<Transform>()->SetPosition(-2, -1, 0);

	gameObject = gameObjectContainer->AddGameObject("DebugText", make_unique<RenderText>());
	RenderText* debugText = static_cast<RenderText*>(gameObject);
	debugText->SetText("Debug text");
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	gameObjectContainer->AddGameObject("Camera", make_unique<Camera>());
	gameObjectContainer->AddGameObject("PlayerShip", make_unique<PlayerShip>());
}

void Scene::LoadScene()
{
	json sceneJson = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	for (const auto gameObjectJson : sceneJson.items())
	{
		string name = gameObjectJson.key();
		string type = gameObjectJson.value()["type"];

		auto gameObject = gameObjectContainer->TryGetGameObject(name);
		if (gameObject == nullptr)
			gameObject = gameObjectContainer->AddGameObject(name, GameObjectFactory::MakeGameObject(type));

		gameObject->SetFromJson(gameObjectJson.value());
	}
}

void Scene::SaveScene() const
{
	json sceneJson;
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetName() != "Camera")
			sceneJson[gameObject->GetName()] = gameObject->GetJson();
	}

	FileSystem::WriteTextToFile(sceneJson.dump(2), GetFileName());
}

void Scene::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SaveKeyPressed")
		SaveScene();
	else if (key == "LoadKeyPressed")
		LoadScene();
}

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}
