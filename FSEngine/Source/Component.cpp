#include "../Header/Component.h"

bool Component::IsType(const type_info& typeInfo)
{
	return this->GetType() == typeInfo;
}

bool Component::IsShared() const
{
	return isShared;
}

void Component::SetShared(bool isShared)
{
	this->isShared = isShared;
}
