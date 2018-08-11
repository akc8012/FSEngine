#include "../Header/SceneManager.h"

SceneManager::SceneManager(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input = input;
	this->window = window;
}

GameObject* SceneManager::AddGameObject(const string& name, GameObject* gameObject)
{
	gameObject->SetSystems(fileSystem, input, window);
	gameObjects.emplace(name, gameObject);

	return gameObject;
}

GameObject* SceneManager::GetGameObject(const string& name) const
{
	return gameObjects.at(name);
}

void SceneManager::Update(float deltaTime)
{
	for (auto& gameObject : gameObjects)
		gameObject.second->Update(deltaTime);
}

void SceneManager::Draw(Renderer* renderer)
{
	for (auto& gameObject : gameObjects)
		renderer->RenderGameObject(gameObject.second);
}

SceneManager::~SceneManager()
{
	for (auto& gameObject : gameObjects)
		delete gameObject.second;
}
