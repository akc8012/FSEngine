#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	components = make_unique<Components>();
	gameObjectContainer = make_unique<GameObjectContainer>(systems, components.get());

	AddGameObjects();
}

void Scene::AddGameObjects()
{
	auto gameObject = gameObjectContainer->AddGameObject("MemeFaceCube", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Texture>("Resource/Image/awesomeface.png"));
	components->transform->Get(gameObject->GetName())->SetPosition(4.5f, 0.2f, 0);

	gameObject = gameObjectContainer->AddGameObject("GreenCube", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.1f, 0.6f, 0.3f));
	components->transform->Get(gameObject->GetName())->SetPosition(6, -0.2f, 0.1f);
	components->transform->Get(gameObject->GetName())->SetScale(2, 0.8f, 2.8f);

	gameObject = gameObjectContainer->AddGameObject("Red", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.8f, 0.f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(1.5f, 1, -3);

	gameObject = gameObjectContainer->AddGameObject("Green", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.f, 0.8f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(1, -1, -1);

	gameObject = gameObjectContainer->AddGameObject("Blue", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.f, 0.f, 0.8f));
	components->transform->Get(gameObject->GetName())->SetPosition(-0.8f, 0, -2);

	gameObject = gameObjectContainer->AddGameObject("Yellow", make_unique<CubePrimitive>());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.6f, 0.6f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(-2, -1, 0);

	for (int i = 0; i < 100; i++)
	{
		auto cube = make_unique<CubePrimitive>();
		gameObject = gameObjectContainer->AddGameObject(std::to_string(i), move(cube));
		components->shading->Add(gameObject->GetName(), make_shared<Shading>(systems->random->GetRandomUniformVector(0.f, 1.f)));
		components->transform->Get(gameObject->GetName())->SetPosition(systems->random->GetRandomUniformVector(-20.f, 20.f));
	}

	gameObject = gameObjectContainer->AddGameObject("DebugText", make_unique<RenderText>());
	RenderText* debugText = dynamic_cast<RenderText*>(gameObject);
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

Components* Scene::GetComponents() const
{
	return components.get();
}

Scene::~Scene()
{
	//SaveScene();
}
