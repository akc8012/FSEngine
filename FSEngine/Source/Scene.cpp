#include "../Header/Scene.h"

Scene::Scene(Systems* systems, Window* window)
{
	this->systems = systems;
	this->window = window;

	gameObjectContainer = make_unique<GameObject::GameObjectContainer>(systems);
	AddGameObjects(window);
}

void Scene::AddGameObjects(Window* window)
{
	gameObjectContainer->AddGameObject("Cube", new CubePrimitive(make_shared<ShadingComponent>(0.f, 0.2f, 0.7f)));
	gameObjectContainer->AddGameObject("Camera", new Camera(window));
}

GameObject::GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}
