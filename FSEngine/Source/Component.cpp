#include "../Header/Component.h"

Component::~Component()
{

}

const string& Component::GetName() const
{
	return name;
}

void Component::SetName(const string& name)
{
	this->name = name;
}
