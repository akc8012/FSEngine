#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input= input;
	this->window = window;
}

void GameObject::AddComponent(MeshComponent* component)
{
	meshComponents.emplace(ComponentTypeString[MeshComponent::ComponentTypeId], component);
}

void GameObject::AddComponent(TextureComponent* component)
{
	textureComponents.emplace(ComponentTypeString[TextureComponent::ComponentTypeId], component);
}

void GameObject::AddComponent(TransformComponent* component)
{
	transformComponents.emplace(ComponentTypeString[TransformComponent::ComponentTypeId], component);
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
