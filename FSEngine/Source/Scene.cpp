#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems, Window* window)
{
	this->name = name;
	this->systems = systems;
	this->window = window;

	gameObjectContainer = make_unique<GameObject::GameObjectContainer>(systems);
	AddGameObjects(window);

	SaveScene();
}

void Scene::AddGameObjects(Window* window)
{
	gameObjectContainer->AddGameObject("Cube", new CubePrimitive(make_shared<ShadingComponent>(0.f, 0.2f, 0.7f)));
	gameObjectContainer->AddGameObject("Camera", new Camera(window));
}

void Scene::SaveScene() const
{
	json j;

	for (const auto& gameObject : gameObjectContainer->GetGameObjects())
		j[gameObject->GetName()] = gameObject->GetJson();

	FileSystem::WriteTextToFile(j.dump(2), "Resource/Json/" + name + ".json");
}

GameObject::GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}
