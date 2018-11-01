#include "../Header/ComponentContainer.h"

namespace ComponentFactory
{
	shared_ptr<Component> MakeComponent(const string& type)
	{
		if (type == Types::ComponentTypeString[Mesh::ComponentTypeId])
			return make_shared<Mesh>();

		else if (type == Types::ComponentTypeString[Color::ComponentTypeId])
			return make_shared<Color>();

		else if (type == Types::ComponentTypeString[Texture::ComponentTypeId])
			return make_shared<Texture>();

		else if (type == Types::ComponentTypeString[FontTexture::ComponentTypeId])
			return make_shared<FontTexture>();

		else if (type == Types::ComponentTypeString[Transform::ComponentTypeId])
			return make_shared<Transform>();

		else if (type == Types::ComponentTypeString[Model::ComponentTypeId])
			return make_shared<Model>();

		throwFS("Cannot make Component of unrecognized type: " + type);
	}
}

ComponentContainer::ComponentContainer()
{
	mesh = make_unique<ComponentCollection<Mesh>>();
	color = make_unique<ComponentCollection<Color>>();
	texture = make_unique<ComponentCollection<Texture>>();
	transform = make_unique<ComponentCollection<Transform>>();
	model = make_unique<ComponentCollection<Model>>();
}

vector<Component*> ComponentContainer::GetAllComponents() const
{
	vector<Component*> components;

	auto meshComponents = mesh->GetComponents();
	components.insert(components.end(), meshComponents.begin(), meshComponents.end());

	auto colorComponents = color->GetComponents();
	components.insert(components.end(), colorComponents.begin(), colorComponents.end());

	auto textureComponents = texture->GetComponents();
	components.insert(components.end(), textureComponents.begin(), textureComponents.end());

	auto transformComponents = transform->GetComponents();
	components.insert(components.end(), transformComponents.begin(), transformComponents.end());

	auto modelComponents = model->GetComponents();
	components.insert(components.end(), modelComponents.begin(), modelComponents.end());

	return components;
}
