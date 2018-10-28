#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);

	AddGameObjects();
	LoadScene();

	systems->eventSystem->AddListener("SaveKeyPressed", this);
	systems->eventSystem->AddListener("LoadKeyPressed", this);
	systems->eventSystem->AddListener("GameStopped", this);
}

void Scene::AddGameObjects()
{

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
		if (!gameObject->GetSerializable())
			continue;

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

	else if (key == "GameStopped")
		SaveScene();
}

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}
