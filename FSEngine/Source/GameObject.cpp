#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem)
{
	this->fileSystem = fileSystem;
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
