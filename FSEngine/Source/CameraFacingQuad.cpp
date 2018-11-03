#include "../Header/CameraFacingQuad.h"

void CameraFacingQuad::Start()
{
	AddComponent(make_shared<QuadMesh>(), "Mesh");
	AddComponent(make_shared<FontTexture>(), "Shading");
}

string CameraFacingQuad::GetGameObjectType() const
{
	return "CameraFacingQuad";
}
