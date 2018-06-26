#include "../Header/Camera.h"

void Camera::CalculateViewMatrix(Uint32 deltaTime)
{
	vec3 forwardVector = vec3(0.0f, 0.0f, -1.0f);
	vec3 upVector = vec3(0.0f, 1.0f, 0.0f);

	const float SpeedMod = 0.005f;
	position += normalize(cross(forwardVector, upVector)) * (Input::GetHorizontalAxis() * SpeedMod * deltaTime);
	position += forwardVector * (-Input::GetVerticalAxis() * SpeedMod * deltaTime);

	viewMatrix = lookAt(position, position + forwardVector, upVector);
}

void Camera::CalculateProjectionMatrix(vec2 windowSize)
{
	const float FieldOfView = radians(45.0f);
	const float AspectRatio = (float)windowSize.x / (float)windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	projectionMatrix = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}

mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}
