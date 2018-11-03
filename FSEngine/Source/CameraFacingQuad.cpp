#include "../Header/CameraFacingQuad.h"

void CameraFacingQuad::Start()
{
	AddComponent(make_shared<QuadMesh>(), "Mesh");
	AddComponent(make_shared<Transform>());

	GetParameterCollection()->SetParameter(DoLateDraw, true);
}

string CameraFacingQuad::GetGameObjectType() const
{
	return "CameraFacingQuad";
}
