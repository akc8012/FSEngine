#include "../Header/SceneManager.h"

SceneManager::SceneManager(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input = input;
	this->window = window;
}

GameObject* SceneManager::AddGameObject(const string& name, GameObject* gameObject, bool lateRefresh)
{
	auto result = gameObjects.emplace(name, gameObject);
	if (!result.second)
		throw "GameObject with name " + name + " already exists";

	gameObject->SetSystems(fileSystem, input, window);
	gameObject->SetLateRefresh(lateRefresh);
	gameObject->Start();

	return gameObject;
}

GameObject* SceneManager::GetGameObject(const string& name) const
{
	GameObject* gameObject = TryGetGameObject(name);
	if (gameObject == nullptr)
		throw (string)"GameObject with name " + name + (string)" not found";

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

void SceneManager::Update(float deltaTime)
{
	UpdateGameObjects(deltaTime, false);
	UpdateGameObjects(deltaTime, true);
}

void SceneManager::UpdateGameObjects(float deltaTime, bool refreshLateGameObjects)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject.second->GetLateRefresh() == refreshLateGameObjects)
			gameObject.second->Update(deltaTime);
	}
}

void SceneManager::Draw(Renderer* renderer)
{
	DrawGameObjects(renderer, false);
	DrawGameObjects(renderer, true);
}

void SceneManager::DrawGameObjects(Renderer* renderer, bool refreshLateGameObjects)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject.second->GetLateRefresh() == refreshLateGameObjects)
			renderer->RenderGameObject(gameObject.second);
	}
}

SceneManager::~SceneManager()
{
	for (auto& gameObject : gameObjects)
		delete gameObject.second;
}
