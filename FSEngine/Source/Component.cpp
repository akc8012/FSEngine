#include "../Header/Component.h"

bool Component::IsType(const type_info& typeInfo)
{
	return this->GetType() == typeInfo;
}
