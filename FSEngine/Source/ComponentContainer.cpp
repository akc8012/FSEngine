#include "../Header/ComponentContainer.h"

namespace ComponentFactory
{
	shared_ptr<Component> MakeComponent(const string& type)
	{
		if (type == Types::ComponentTypeToString(Mesh::ComponentTypeId))
			return make_shared<Mesh>();

		if (type == Types::ComponentTypeToString(QuadMesh::ComponentTypeId))
			return make_shared<QuadMesh>();

		if (type == Types::ComponentTypeToString(CubeMesh::ComponentTypeId))
			return make_shared<CubeMesh>();

		else if (type == Types::ComponentTypeToString(Color::ComponentTypeId))
			return make_shared<Color>();

		else if (type == Types::ComponentTypeToString(Texture::ComponentTypeId))
			return make_shared<Texture>();

		else if (type == Types::ComponentTypeToString(FontTexture::ComponentTypeId))
			return make_shared<FontTexture>();

		else if (type == Types::ComponentTypeToString(Transform::ComponentTypeId))
			return make_shared<Transform>();

		else if (type == Types::ComponentTypeToString(Transform2D::ComponentTypeId))
			return make_shared<Transform2D>();

		else if (type == Types::ComponentTypeToString(Model::ComponentTypeId))
			return make_shared<Model>();

		throwFS("Cannot make Component of unrecognized type: " + type);
	}
}

ComponentContainer::ComponentContainer()
{
	mesh = make_unique<ComponentCollection<Mesh>>();
	shading = make_unique<ComponentCollection<Shading>>();
	transform = make_unique<ComponentCollection<Transform>>();
	model = make_unique<ComponentCollection<Model>>();
}

vector<Component*> ComponentContainer::GetAllComponents() const
{
	vector<Component*> components;

	auto meshComponents = mesh->GetComponents();
	components.insert(components.end(), meshComponents.begin(), meshComponents.end());

	auto shadingComponents = shading->GetComponents();
	components.insert(components.end(), shadingComponents.begin(), shadingComponents.end());

	auto transformComponents = transform->GetComponents();
	components.insert(components.end(), transformComponents.begin(), transformComponents.end());

	auto modelComponents = model->GetComponents();
	components.insert(components.end(), modelComponents.begin(), modelComponents.end());

	return components;
}
