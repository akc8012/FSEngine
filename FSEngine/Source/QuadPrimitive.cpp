#include "../Header/QuadPrimitive.h"

void QuadPrimitive::Start()
{
	AddComponent(make_shared<QuadMesh>(), "Mesh");
	AddComponent(make_shared<Transform>());
}

string QuadPrimitive::GetGameObjectType() const
{
	return "QuadPrimitive";
}
