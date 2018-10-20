#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);
	AddGameObjects();
}

void Scene::AddGameObjects()
{
	auto gameObject = gameObjectContainer->AddGameObject("BlueCube", make_unique<CubePrimitive>());
	gameObject->AddComponent(make_shared<Shading>(0.f, 0.f, 0.8f));

	gameObjectContainer->AddGameObject("Camera", make_unique<Camera>());
}

void Scene::LoadScene()
{
	json j = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetName() != "Camera")
			gameObject->SetFromJson(j[gameObject->GetName()]);
	}
}

void Scene::SaveScene() const
{
	json j;
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetName() != "Camera")
			j[gameObject->GetName()] = gameObject->GetJson();
	}

	FileSystem::WriteTextToFile(j.dump(2), GetFileName());
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
	SaveScene();
}
