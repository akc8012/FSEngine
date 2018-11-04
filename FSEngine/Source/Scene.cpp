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
	systems->eventSystem->SendEvent("BeforeSceneLoad", nullptr, false);

	json sceneJson = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	vector<string> loadedGameObjectNames = LoadGameObjectsFromJson(sceneJson);
	RemoveUnloadedGameObjects(loadedGameObjectNames);

	systems->eventSystem->SendEvent("SceneLoaded", nullptr, false);
	for (auto gameObject : gameObjectContainer->GetGameObjects())
		gameObject->SceneLoaded();
}

vector<string> Scene::LoadGameObjectsFromJson(const json& j)
{
	vector<string> loadedGameObjectNames;

	for (const auto gameObjectJson : j.items())
	{
		string name = gameObjectJson.key();
		loadedGameObjectNames.push_back(name);

		IGameObject* gameObject = gameObjectContainer->TryGetGameObject(name);
		if (gameObject == nullptr)
		{
			string type = gameObjectJson.value()["type"];
			gameObject = gameObjectContainer->AddGameObject(name, GameObjectFactory::MakeGameObject(type));
		}

		gameObject->SetFromJson(gameObjectJson.value());
	}

	return loadedGameObjectNames;
}

void Scene::RemoveUnloadedGameObjects(const vector<string>& loadedGameObjectNames)
{
	for (const IGameObject* gameObject : gameObjectContainer->GetGameObjects())
	{
		string name = gameObject->GetName();
		if (GameObjectIsLoaded(name, loadedGameObjectNames))
			continue;

		gameObjectContainer->RemoveGameObject(name);
	}
}

bool Scene::GameObjectIsLoaded(const string& name, const vector<string>& loadedGameObjectNames)
{
	return std::find(loadedGameObjectNames.begin(), loadedGameObjectNames.end(), name) != loadedGameObjectNames.end();
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
