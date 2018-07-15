#include "../Header/Component.h"

Component::~Component()
{

}

ComponentType Component::GetType() const
{
	return componentType;
}

bool Component::IsShared() const
{
	return isShared;
}

void Component::SetShared(bool isShared)
{
	this->isShared = isShared;
}
