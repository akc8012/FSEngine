#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "Window.h"
#include "MeshComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include <vector>
using std::vector;

class GameObject
{
protected:
	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	Window* window = nullptr;

private:
	vector<vector<Component*>*> componentLists;

	vector<MeshComponent*> meshComponents;
	vector<TextureComponent*> textureComponents;
	vector<TransformComponent*> transformComponents;

	//vector<Component*> GetList(ComponentType componentType) const;

public:
	GameObject(FileSystem* fileSystem, Input* input, Window* window);
	~GameObject();

	void AddComponent(MeshComponent* component);
	void AddComponent(TextureComponent* component);
	void AddComponent(TransformComponent* component);

	template <typename T> T* GetComponent() const;
	virtual void Update(float deltaTime);
};

template <typename T> inline T* GameObject::GetComponent() const
{
	T* component = nullptr;

	if (meshComponents.size() > 0 && typeid(T) == typeid(MeshComponent))
		component = reinterpret_cast<T*>(meshComponents[0]);

	if (textureComponents.size() > 0 && typeid(T) == typeid(TextureComponent))
		component = reinterpret_cast<T*>(textureComponents[0]);

	if (transformComponents.size() > 0 && typeid(T) == typeid(TransformComponent))
		component = reinterpret_cast<T*>(transformComponents[0]);

	return component;
}
