#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems, Window* window)
{
	this->name = name;
	this->systems = systems;
	this->window = window;

	components = make_unique<Components>();
	gameObjectContainer = make_unique<GameObject::GameObjectContainer>(systems, components.get());

	AddGameObjects(window);
}

void Scene::AddGameObjects(Window* window)
{
	auto gameObject = gameObjectContainer->AddGameObject("GreenCube", new CubePrimitive());
	components->transform->Get(gameObject->GetName())->SetPosition(6, -0.2f, 0.1f);
	components->transform->Get(gameObject->GetName())->SetScale(2, 0.8f, 2.8f);

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

const Components* Scene::GetComponents() const
{
	return components.get();
}

Scene::~Scene()
{
	//SaveScene();
}
