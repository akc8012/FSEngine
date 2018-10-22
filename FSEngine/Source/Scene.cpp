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
	gameObjectContainer->AddGameObject("Cube", make_unique<CubePrimitive>());
	gameObjectContainer->AddGameObject("Camera", make_unique<Camera>());
}

void Scene::LoadScene()
{
	json sceneJson = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->GetName() != "Camera")
			gameObject->SetFromJson(sceneJson[gameObject->GetName()]);
	}

	printFS("Load!");
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

	printFS("Save!");
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

Scene::~Scene()
{
	SaveScene();
}
