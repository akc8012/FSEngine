#include "../Header/Component.h"

Component::~Component()
{

}

Types::ComponentType Component::GetComponentTypeId() const
{
	return ComponentTypeId;
}

const string& Component::GetName() const
{
	return name;
}

void Component::SetName(const string& name)
{
	this->name = name;
}
