#include "../Header/CubePrimitive.h"

void CubePrimitive::Start()
{
	Mesh* meshComponent = AddComponent(make_shared<CubeMesh>(), "Mesh");
	meshComponent->GetParameterCollection()->SetParameter(Mesh::DrawElements, false);
	meshComponent->GetParameterCollection()->SetParameter(Mesh::RenderBackfaces, true);

	AddComponent(make_shared<Transform>());
}

void CubePrimitive::Update()
{

}

string CubePrimitive::GetGameObjectType() const
{
	return "CubePrimitive";
}
