#include "../Header/Camera.h"

Camera::Camera(Window* window)
{
	this->window = window;

	viewTransform = AddComponent(make_shared<TransformComponent>(), "View").get();
	ResetViewTransform();

	AddComponent(make_shared<TransformComponent>(), "Perspective");
	AddComponent(make_shared<TransformComponent>(), "Orthographic");

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
	vec3 forward = TransformComponent::Forward;

	if (systems->fileSystem->GetSettingsValue<bool>("CameraControl"))
	{
		direction += GetDirectionInput() * GetFrameAdjustedSpeed();
		direction.x = ClampPitch(direction.x);

		forward = TransformComponent::EulerAngleToDirectionVector(direction);

		vec3 right = glm::normalize(glm::cross(forward, TransformComponent::Up));
		position += GetFloorMovementInput(forward, right) * GetFrameAdjustedSpeed();
		position.y += GetHeightInput() * GetFrameAdjustedSpeed();
	}

	SetDebugText(TransformComponent::GetVectorString(direction));
	viewTransform->LookAt(position, position + forward, TransformComponent::Up);
}

vec3 Camera::GetDirectionInput() const
{
	float pitchInputValue = systems->input->GetDigitalAxis(SDL_SCANCODE_I, SDL_SCANCODE_K);
	float yawInputValue = systems->input->GetDigitalAxis(SDL_SCANCODE_L, SDL_SCANCODE_J);

	return vec3(glm::degrees(pitchInputValue), glm::degrees(yawInputValue), 0);
}

float Camera::ClampPitch(float pitch) const
{
	if (std::abs(pitch) >= 90.f)
		return 89.999f * (pitch > 0 ? 1 : -1);

	return pitch;
}

vec3 Camera::GetFloorMovementInput(const vec3& forward, const vec3& right) const
{
	vec3 verticalInput = -systems->input->GetVerticalAxis() * glm::normalize(vec3(forward.x, 0, forward.z));
	vec3 horizontalInput = systems->input->GetHorizontalAxis() * right;

	return verticalInput + horizontalInput;
}

float Camera::GetHeightInput() const
{
	return systems->input->GetDigitalAxis(SDL_SCANCODE_R, SDL_SCANCODE_F);
}

float Camera::GetFrameAdjustedSpeed() const
{
	return systems->fileSystem->GetSettingsValue<float>("CameraSpeed") * systems->gameTimer->GetDeltaTime();
}

void Camera::SetDebugText(const string& text) const
{
	dynamic_cast<RenderText*>(gameObjectContainer->GetGameObject("DebugText"))->SetText(text);
}

void Camera::CalculateProjectionMatrixPerspective()
{
	vec2 windowSize = window->GetWindowSize();

	const float FieldOfView = glm::radians(45.0f);
	const float AspectRatio = windowSize.x / windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	GetComponent<TransformComponent>("Perspective")->SetMatrix(glm::perspective(FieldOfView, AspectRatio, NearPlane, FarPlane));
}

void Camera::CalculateProjectionMatrixOrthographic()
{
	const float Left = -1.0f;
	const float Right = 1.0f;
	const float Bottom = Left;
	const float Top = Right;

	GetComponent<TransformComponent>("Orthographic")->SetMatrix(glm::ortho(Left, Right, Bottom, Top));
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
