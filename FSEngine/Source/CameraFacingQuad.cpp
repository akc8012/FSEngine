#include "../Header/CameraFacingQuad.h"

void CameraFacingQuad::Start()
{
	AddComponent(make_shared<QuadMesh>(), "Mesh");
	AddComponent(make_shared<Transform>());

	GetParameterCollection()->SetParameter(DoLateDraw, true);
	GetParameterCollection()->SetParameter(DoLateUpdate, true);
}

void CameraFacingQuad::SceneLoaded()
{
	camera = gameObjectContainer->GetGameObjectAs<Camera>("Camera");
	transform = GetComponent<Transform>();
}

void CameraFacingQuad::Update()
{
	vec3 cameraForward = camera->GetForward();
	vec3 lookDirection(cameraForward.x, -cameraForward.y, -cameraForward.z);

	transform->SetOrientation(FSMath::LookAt(lookDirection, camera->GetUp()));
}

string CameraFacingQuad::GetGameObjectType() const
{
	return "CameraFacingQuad";
}
