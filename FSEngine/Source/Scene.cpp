#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);
	AddGameObjects();
}

void Scene::AddGameObjects()
{
	auto gameObject = gameObjectContainer->AddGameObject("Cube", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.f, 0.2f, 0.8f));

	auto newTransform = gameObject->AddComponent(make_shared<NewTransform>());
	//newTransform->SetPosition(vec3(1, 0, 0));
	//newTransform->SetScale(vec3(0.5f, 1, 0.5f));

	/*gameObject = gameObjectContainer->AddGameObject("GreenCube", make_unique<CubePrimitive>());
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

	for (int i = 0; i < 100; i++)
	{
		auto cube = make_unique<CubePrimitive>();
		gameObject = gameObjectContainer->AddGameObject(std::to_string(i), move(cube));
		gameObject->AddComponent(make_shared<Shading>(systems->random->GetRandomUniformVector(0.f, 1.f)));
		gameObject->GetComponent<Transform>()->SetPosition(systems->random->GetRandomUniformVector(-20.f, 20.f));
	}

	gameObject = gameObjectContainer->AddGameObject("DebugText", make_unique<RenderText>());
	RenderText* debugText = dynamic_cast<RenderText*>(gameObject);
	debugText->SetText("Debug text");
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));*/

	gameObjectContainer->AddGameObject("Camera", make_unique<Camera>());
	//gameObjectContainer->AddGameObject("PlayerShip", make_unique<PlayerShip>());
}

void Scene::LoadScene()
{
	//json j = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	//for (const auto& gameObject : gameObjectContainer->GetGameObjects())
	//	gameObject->SetFromJson(j[gameObject->GetName()]);
}

void Scene::SaveScene() const
{
	//json j;
	//for (const auto& gameObject : gameObjectContainer->GetGameObjects())
	//	j[gameObject->GetName()] = gameObject->GetJson();

	//FileSystem::WriteTextToFile(j.dump(2), GetFileName());
}

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}

Scene::~Scene()
{
	//SaveScene();
}
