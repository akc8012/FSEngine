#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input= input;
	this->window = window;
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::Update(float deltaTime)
{

}

GameObject::~GameObject()
{
	for (auto& component : components)
	{
		if (!component->IsShared())
			delete component;
	}
}
