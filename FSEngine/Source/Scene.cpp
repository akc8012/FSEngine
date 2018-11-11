#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);
	LoadScene();

	systems->eventSystem->AddListener("SaveKeyPressed", this);
	systems->eventSystem->AddListener("LoadKeyPressed", this);
	systems->eventSystem->AddListener("GameStopped", this);
	systems->eventSystem->AddListener("WindowFocusGained", this);
	systems->eventSystem->AddListener("WindowFocusLost", this);
}

void Scene::LoadScene()
{
	systems->eventSystem->SendEvent("BeforeSceneLoad", nullptr, false);

	json sceneJson = TryParseSceneJson();
	if (sceneJson == nullptr)
		return;

	RemoveUnloadedGameObjects(sceneJson);
	LoadGameObjectsFromJson(sceneJson);

	SendSceneLoadedEvents();
}

json Scene::TryParseSceneJson() const
{
	try
	{
		return json::parse(FileSystem::LoadTextFromFile(GetFileName()));
	}
	catch (const nlohmann::detail::parse_error& e)
	{
		if (SceneLoaded())
		{
			printFS("Error: Json parse_error thrown while parsing scene, reverting to loaded scene: " + string(e.what()));
			return nullptr;
		}

		throw e;
	}
}

bool Scene::SceneLoaded() const
{
	return gameObjectContainer->GetGameObjectCount() != 0;
}

void Scene::RemoveUnloadedGameObjects(const json& sceneJson)
{
	for (const IGameObject* gameObject : gameObjectContainer->GetGameObjects())
	{
		string name = gameObject->GetName();

		auto foundGameObject = sceneJson.find(name);
		if (foundGameObject != sceneJson.end())
			continue;

		gameObjectContainer->RemoveGameObject(name);
	}
}

void Scene::LoadGameObjectsFromJson(const json& j)
{
	for (const auto gameObjectJson : j.items())
	{
		string name = gameObjectJson.key();

		IGameObject* gameObject = gameObjectContainer->TryGetGameObject(name);
		if (gameObject == nullptr)
		{
			string type = gameObjectJson.value()["type"];
			gameObject = gameObjectContainer->AddGameObject(name, GameObjectFactory::MakeGameObject(type));
		}

		gameObject->SetFromJson(gameObjectJson.value());
	}
}

void Scene::SendSceneLoadedEvents()
{
	systems->eventSystem->SendEvent("SceneLoaded", nullptr, false);
	for (auto gameObject : gameObjectContainer->GetGameObjects())
		gameObject->SceneLoaded();
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
	if (key == "SaveKeyPressed" || key == "GameStopped")
		SaveScene();

	if (key == "LoadKeyPressed")
		LoadScene();

	if (key == "WindowFocusGained" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus"))
		LoadScene();

	if (key == "WindowFocusLost" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus"))
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

Scene::~Scene()
{
	systems->eventSystem->RemoveListener(this);
}
