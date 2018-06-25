#include "../Header/GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	if (renderComponent != NULL)
		delete renderComponent;

	if (transformComponent != NULL)
		delete transformComponent;
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
