#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems)
 : name(name), systems(systems)
{
	gameObjectContainer = make_unique<GameObjectContainer>(systems);
	LoadScene();
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
		LoadGameObjectFromJson(name, gameObjectJson.value());
	}
}

void Scene::LoadGameObjectFromJson(const string& name, const json& j)
{
	IGameObject* gameObject = gameObjectContainer->TryGetGameObject(name);
	if (gameObject == nullptr)
	{
		string type = j["type"];
		gameObject = gameObjectContainer->AddGameObject(name, GameObjectFactory::MakeGameObject(type));
	}

	gameObject->SetFromJson(j);
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

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}
