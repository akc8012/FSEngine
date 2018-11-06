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
	vec3 direction = camera->GetPosition() - transform->GetPosition();
	transform->SetOrientation(FSMath::LookAt(direction, camera->GetUp()));
}

string CameraFacingQuad::GetGameObjectType() const
{
	return "CameraFacingQuad";
}
