#include "../Header/Component.h"

bool Component::IsShared() const
{
	return isShared;
}

void Component::SetShared(bool isShared)
{
	this->isShared = isShared;
}

Component::~Component()
{

}
