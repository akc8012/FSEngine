#include "../Header/ComponentType.h"

namespace Types
{
	ComponentType StringToComponentType(const string& componentString)
	{
		return (ComponentType)std::distance(ComponentTypeString, std::find(ComponentTypeString, ComponentTypeString + ComponentsLength, componentString));
	}
}
