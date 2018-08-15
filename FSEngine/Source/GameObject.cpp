#include "../Header/GameObject.h"

GameObject::GameObject()
{
	meshComponents = new unordered_map<string, MeshComponent*>();
	shadingComponents = new unordered_map<string, ShadingComponent*>();
	transformComponents = new unordered_map<string, TransformComponent*>();
}

void GameObject::SetSystems(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input = input;
	this->window = window;
}

void GameObject::Start()
{

}

MeshComponent* GameObject::AddComponent(MeshComponent* component, string name)
{
	auto result = meshComponents->emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

ShadingComponent* GameObject::AddComponent(ShadingComponent* component, string name)
{
	auto result = shadingComponents->emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

TransformComponent* GameObject::AddComponent(TransformComponent* component, string name)
{
	auto result = transformComponents->emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

void GameObject::ThrowDuplicateNameException(const string& name) const
{
	throw "Component with name " + name + " already exists";
}

void GameObject::Update(float deltaTime)
{

}

void GameObject::SetLateRefresh(bool lateRefresh)
{
	this->lateRefresh = lateRefresh;
}

bool GameObject::GetLateRefresh() const
{
	return lateRefresh;
}

GameObject::~GameObject()
{
	for (auto& meshComponent : *meshComponents)
	{
		if (!meshComponent.second->IsShared())
			delete meshComponent.second;
	}

	for (auto& textureComponent : *shadingComponents)
	{
		if (!textureComponent.second->IsShared())
			delete textureComponent.second;
	}

	for (auto& transformComponent : *transformComponents)
	{
		if (!transformComponent.second->IsShared())
			delete transformComponent.second;
	}

	delete transformComponents;
	delete shadingComponents;
	delete meshComponents;
}
