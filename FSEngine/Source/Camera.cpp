#include "../Header/Camera.h"

Camera::Camera(FileSystem* fileSystem, Window* window)
 : GameObject(fileSystem)
{
	this->window = window;

	transformComponent = new TransformComponent();
	transformComponent->SetPosition(vec3(0, 0, -3));
}

void Camera::Update(Uint32 deltaTime)
{
	CalculateViewMatrix(deltaTime);
	CalculateProjectionMatrixPerspective();
}

void Camera::CalculateViewMatrix(Uint32 deltaTime)
{
	vec3 forwardVector = vec3(0.0f, 0.0f, -1.0f);
	vec3 upVector = vec3(0.0f, 1.0f, 0.0f);

	const float SpeedMod = 0.005f;
	vec3 position = -transformComponent->GetPosition();
	position += normalize(cross(forwardVector, upVector)) * (Input::GetHorizontalAxis() * SpeedMod * deltaTime);
	position += forwardVector * (-Input::GetVerticalAxis() * SpeedMod * deltaTime);

	transformComponent->LookAt(position, forwardVector, upVector);
}

void Camera::CalculateProjectionMatrixPerspective()
{
	vec2 windowSize = window->GetWindowSize();

	const float FieldOfView = radians(45.0f);
	const float AspectRatio = windowSize.x / windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	projectionMatrix = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}

void Camera::CalculateProjectionMatrixOrthographic()
{
	vec2 windowSize = window->GetWindowSize();

	const float Left = 0.0f;
	const float Right = 1.5f;
	const float Bottom = 0.0f;
	const float Top = 1.5f;

	projectionMatrix = ortho(Left, Right, Bottom, Top);
}

mat4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}
