#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems, Window* window)
{
	this->name = name;
	this->systems = systems;
	this->window = window;

	gameObjectContainer = make_unique<GameObject::GameObjectContainer>(systems);
	AddGameObjects(window);

	LoadScene();
}

void Scene::AddGameObjects(Window* window)
{
	gameObjectContainer->AddGameObject("Cube", new CubePrimitive(make_shared<ShadingComponent>(0.f, 0.2f, 0.7f)));
	gameObjectContainer->AddGameObject("Camera", new Camera(window));
}

void Scene::LoadScene()
{
	json j = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	for (const auto& gameObject : gameObjectContainer->GetGameObjects())
		gameObject->SetFromJson(j[gameObject->GetName()]);
}

void Scene::SaveScene() const
{
	json j;
	for (const auto& gameObject : gameObjectContainer->GetGameObjects())
		j[gameObject->GetName()] = gameObject->GetJson();

	FileSystem::WriteTextToFile(j.dump(2), GetFileName());
}

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObject::GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}

Scene::~Scene()
{
	SaveScene();
}
