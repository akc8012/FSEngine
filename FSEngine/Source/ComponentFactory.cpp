#include "../Header/ComponentFactory.h"

shared_ptr<Component> ComponentFactory::MakeComponent(const string& type)
{
	if (type == Types::ComponentTypeString[Mesh::ComponentTypeId])
		return make_shared<Mesh>();

	else if (type == Types::ComponentTypeString[Shading::ComponentTypeId])
		return make_shared<Shading>();

	else if (type == Types::ComponentTypeString[Transform::ComponentTypeId])
		return make_shared<Transform>();

	throwFS("Cannot make Component of unrecognized type: " + type);
}
