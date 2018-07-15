#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem, Input* input, Window* window)
{
	this->fileSystem = fileSystem;
	this->input= input;
	this->window = window;

	//componentLists.push_back(&meshComponents);
	//componentLists.push_back(&textureComponents);
	//componentLists.push_back(&transformComponents);
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

//vector<Component*> GameObject::GetList(ComponentType componentType) const
//{
//	switch (componentType)
//	{
//	case Mesh:
//		return meshComponents;
//	case Texture:
//		return textureComponents;
//	case Transform:
//		return transformComponents;
//	default:
//		throw "Could not find component list: " + std::to_string(componentType);
//	}
//}

void GameObject::Update(float deltaTime)
{

}

GameObject::~GameObject()
{
	for (auto& componentList : componentLists)
	{
		for (auto& component : *componentList)
			delete component;
	}
}
