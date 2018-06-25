#include "../Header/GameObject.h"

GameObject::GameObject()
{

}

RenderComponent* GameObject::GetRenderComponent()
{
	return renderComponent;
}

TransformComponent* GameObject::GetTransformComponent()
{
	return transformComponent;
}

void GameObject::Update()
{

}

GameObject::~GameObject()
{
	if (renderComponent != NULL)
		delete renderComponent;

	if (transformComponent != NULL)
		delete transformComponent;
}
