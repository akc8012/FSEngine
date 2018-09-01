#include "../Header/Camera.h"

Camera::Camera(Window* window)
{
	this->window = window;

	viewTransform = AddComponent(new TransformComponent(), "View");
	ResetViewTransform();

	AddComponent(new TransformComponent(), "Perspective");
	AddComponent(new TransformComponent(), "Orthographic");

	GetParameterCollection()->SetParameter(GameObject::DoLateUpdate, true);
	GetParameterCollection()->SetParameter(GameObject::DoDraw, false);
}

void Camera::ResetViewTransform()
{
	SetPosition(vec3(0, 0, 4));
	SetDirection(vec3(0, -90, 0));
}

void Camera::Update()
{
	if (systems->input->IsButtonPressed(SDL_SCANCODE_P))
		ResetViewTransform();

	CalculateViewMatrix();
	CalculateProjectionMatrixPerspective();
	CalculateProjectionMatrixOrthographic();
}

void Camera::CalculateViewMatrix()
{
	if (systems->fileSystem->GetSettingsValue<bool>("CameraControl"))
	{
		vec3 wasdInputVector = vec3(systems->input->GetHorizontalAxis(), 0, systems->input->GetVerticalAxis());
		if (glm::length(wasdInputVector) != 0)
			wasdInputVector = glm::normalize(wasdInputVector);

		position += wasdInputVector * GetFrameAdjustedSpeed();

		float rfInputValue = systems->input->GetDigitalAxis(SDL_SCANCODE_R, SDL_SCANCODE_F);
		position.y += rfInputValue * GetFrameAdjustedSpeed();

		float pitchInputValue = systems->input->GetDigitalAxis(SDL_SCANCODE_I, SDL_SCANCODE_K);
		float yawInputValue = systems->input->GetDigitalAxis(SDL_SCANCODE_L, SDL_SCANCODE_J);

		const float RotationSpeedModifier = 10;
		direction += vec3(pitchInputValue, yawInputValue, 0) * (GetFrameAdjustedSpeed() * RotationSpeedModifier);
	}

	vec3 upVector = vec3(0.0f, 1.0f, 0.0f);
	viewTransform->LookAt(position, position + TransformComponent::EulerAngleToDirectionVector(direction), upVector);
}

float Camera::GetFrameAdjustedSpeed() const
{
	return systems->fileSystem->GetSettingsValue<float>("CameraSpeed") * systems->gameTimer->GetDeltaTime();
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
	const float Left = -1.0f;
	const float Right = 1.0f;
	const float Bottom = Left;
	const float Top = Right;

	GetComponent<TransformComponent>("Orthographic")->SetMatrix(ortho(Left, Right, Bottom, Top));
}

void Camera::SetPosition(const vec3& position)
{
	this->position = position;
}

vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::SetDirection(const vec3& direction)
{
	this->direction = direction;
}

vec3 Camera::GetDirection() const
{
	return direction;
}
