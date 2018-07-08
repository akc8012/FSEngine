#include "../Header/Camera.h"

Camera::Camera(FileSystem* fileSystem, Input* input, Window* window)
 : GameObject(fileSystem, input)
{
	this->window = window;

	AddComponent(new TransformComponent());
	GetComponent<TransformComponent>()->SetPosition(vec3(0, 0, -4));
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

	const float SpeedMod = 4;
	vec3 position = -GetComponent<TransformComponent>()->GetPosition();
	position += normalize(cross(forwardVector, upVector)) * (input->GetHorizontalAxis() * SpeedMod * deltaTime);
	position += forwardVector * (-input->GetVerticalAxis() * SpeedMod * deltaTime);

	GetComponent<TransformComponent>()->LookAt(position, forwardVector, upVector);
}

void Camera::CalculateProjectionMatrixPerspective()
{
	vec2 windowSize = window->GetWindowSize();

	const float FieldOfView = radians(45.0f);
	const float AspectRatio = windowSize.x / windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	projectionPerspective = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}

void Camera::CalculateProjectionMatrixOrthographic()
{
	vec2 windowSize = window->GetWindowSize();

	const float Left = -1.0f;
	const float Right = 1.0f;
	const float Bottom = Left;
	const float Top = Right;

	projectionOrthographic = ortho(Left, Right, Bottom, Top);
}

mat4 Camera::GetProjectionPerspective() const
{
	return projectionPerspective;
}

mat4 Camera::GetProjectionOrthographic() const
{
	return projectionOrthographic;
}
