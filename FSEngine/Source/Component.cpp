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

json Component::GetJson() const
{
	json j;
	j["type"] = Types::ComponentTypeString[GetComponentTypeId()];

	return j;
}

void Component::SetFromJson(const json& j)
{

}

void Component::SetSerializable(bool serializable)
{
	this->serializable = serializable;
}

bool Component::GetSerializable() const
{
	return serializable;
}
