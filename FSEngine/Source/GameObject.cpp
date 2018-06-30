#include "../Header/GameObject.h"

GameObject::GameObject(FileSystem* fileSystem)
{
	this->fileSystem = fileSystem;
}

RenderComponent* GameObject::GetRenderComponent() const
{
	return renderComponent;
}

TransformComponent* GameObject::GetTransformComponent() const
{
	return transformComponent;
}

TextureComponent* GameObject::GetTextureComponent() const
{
	return textureComponent;
}

void GameObject::SetRenderComponent(RenderComponent* renderComponent)
{
	this->renderComponent = renderComponent;
}

void GameObject::SetTransformComponent(TransformComponent* transformComponent)
{
	this->transformComponent = transformComponent;
}

void GameObject::SetTextureComponent(TextureComponent* textureComponent)
{
	this->textureComponent = textureComponent;
}

void GameObject::Update(Uint32 deltaTime)
{

}

GameObject::~GameObject()
{
	if (renderComponent != nullptr)
		delete renderComponent;

	if (transformComponent != nullptr)
		delete transformComponent;
}
