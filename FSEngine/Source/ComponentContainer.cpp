#include "../Header/ComponentContainer.h"

ComponentContainer::ComponentContainer()
{
	mesh = make_unique<ComponentCollection<Mesh>>();
	shading = make_unique<ComponentCollection<Shading>>();
	texture = make_unique<ComponentCollection<Texture>>();
	transform = make_unique<ComponentCollection<Transform>>();
}

vector<Component*> ComponentContainer::GetAllComponents() const
{
	vector<Component*> components;

	auto meshComponents = mesh->GetComponents();
	components.insert(components.end(), meshComponents.begin(), meshComponents.end());

	auto shadingComponents = shading->GetComponents();
	components.insert(components.end(), shadingComponents.begin(), shadingComponents.end());

	auto textureComponents = texture->GetComponents();
	components.insert(components.end(), textureComponents.begin(), textureComponents.end());

	auto transformComponents = transform->GetComponents();
	components.insert(components.end(), transformComponents.begin(), transformComponents.end());

	return components;
}
