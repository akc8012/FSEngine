#include "../Header/Camera.h"

Camera::Camera()
{
	AddComponent(new TransformComponent(), "View");
	AddComponent(new TransformComponent(), "Perspective");
	AddComponent(new TransformComponent(), "Orthographic");

	GetComponent<TransformComponent>("View")->SetPosition(vec3(0, 0, -4));
}

void Camera::Update(float deltaTime)
{
	CalculateViewMatrix(deltaTime);
	CalculateProjectionMatrixPerspective();
	CalculateProjectionMatrixOrthographic();
}

void Camera::CalculateViewMatrix(float deltaTime)
{
	vec3 forwardVector = vec3(0.0f, 0.0f, -1.0f);
	vec3 upVector = vec3(0.0f, 1.0f, 0.0f);

	vec3 position = -GetComponent<TransformComponent>("View")->GetPosition();
	if (fileSystem->GetSettingsValue<bool>("CameraControl"))
	{
		const float SpeedMod = 4;
		position += normalize(cross(forwardVector, upVector)) * (input->GetHorizontalAxis() * SpeedMod * deltaTime);
		position += forwardVector * (-input->GetVerticalAxis() * SpeedMod * deltaTime);
	}

	GetComponent<TransformComponent>("View")->LookAt(position, forwardVector, upVector);
}

void Camera::CalculateProjectionMatrixPerspective()
{
	vec2 windowSize = window->GetWindowSize();

	const float FieldOfView = radians(45.0f);
	const float AspectRatio = windowSize.x / windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	GetComponent<TransformComponent>("Perspective")->SetMatrix(perspective(FieldOfView, AspectRatio, NearPlane, FarPlane));
}

void Camera::CalculateProjectionMatrixOrthographic()
{
	vec2 windowSize = window->GetWindowSize();

	const float Left = -1.0f;
	const float Right = 1.0f;
	const float Bottom = Left;
	const float Top = Right;

	GetComponent<TransformComponent>("Orthographic")->SetMatrix(ortho(Left, Right, Bottom, Top));
}
