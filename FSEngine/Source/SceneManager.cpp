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
	auto result = gameObjects.emplace(name, gameObject);
	if (!result.second)
		throw "GameObject with name " + name + " already exists";

	return gameObject;
}

GameObject* SceneManager::TryGetGameObject(const string& name) const
{
	try
	{
		return gameObjects.at(name);
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}
}

GameObject* SceneManager::GetGameObject(const string& name) const
{
	try
	{
		return gameObjects.at(name);
	}
	catch (std::out_of_range)
	{
		throw "GameObject with name " + name + " not found";
	}
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
