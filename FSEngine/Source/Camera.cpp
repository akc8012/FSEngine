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

mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}
