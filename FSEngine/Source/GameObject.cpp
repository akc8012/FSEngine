#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input= input;
	this->window = window;
}

void GameObject::AddComponent(MeshComponent* component)
{
	meshComponents.push_back(component);
}

void GameObject::AddComponent(TextureComponent* component)
{
	textureComponents.push_back(component);
}

void GameObject::AddComponent(TransformComponent* component)
{
	transformComponents.push_back(component);
}

void GameObject::Update(float deltaTime)
{

}

GameObject::~GameObject()
{
	for (auto& meshComponent : meshComponents)
	{
		if (!meshComponent->IsShared())
			delete meshComponent;
	}

	for (auto& textureComponent : textureComponents)
	{
		if (!textureComponent->IsShared())
			delete textureComponent;
	}

	for (auto& transformComponent : transformComponents)
	{
		if (!transformComponent->IsShared())
			delete transformComponent;
	}
}
