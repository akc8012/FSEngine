#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input= input;
	this->window = window;
}

void GameObject::AddComponent(MeshComponent* component, string name)
{
	auto result = meshComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);
}

void GameObject::AddComponent(TextureComponent* component, string name)
{
	auto result = textureComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);
}

void GameObject::AddComponent(TransformComponent* component, string name)
{
	auto result = transformComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);
}

void GameObject::ThrowDuplicateNameException(const string& name) const
{
	throw "Component with name " + name + " already exists";
}

void GameObject::Update(float deltaTime)
{

}

GameObject::~GameObject()
{
	for (auto& meshComponent : meshComponents)
	{
		if (!meshComponent.second->IsShared())
			delete meshComponent.second;
	}

	for (auto& textureComponent : textureComponents)
	{
		if (!textureComponent.second->IsShared())
			delete textureComponent.second;
	}

	for (auto& transformComponent : transformComponents)
	{
		if (!transformComponent.second->IsShared())
			delete transformComponent.second;
	}
}
