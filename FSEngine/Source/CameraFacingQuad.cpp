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
	mat4 viewMatrix = camera->GetComponent<Transform>("View")->GetMatrix();
	vec3 cameraUp(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

	vec3 direction = camera->GetPosition() - transform->GetPosition();
	transform->SetOrientation(FSMath::LookAt(direction, cameraUp));
}

string CameraFacingQuad::GetGameObjectType() const
{
	return "CameraFacingQuad";
}
