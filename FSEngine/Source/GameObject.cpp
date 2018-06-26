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

void GameObject::Update(Uint32 deltaTime)
{

}

GameObject::~GameObject()
{
	if (renderComponent != NULL)
		delete renderComponent;

	if (transformComponent != NULL)
		delete transformComponent;
}
