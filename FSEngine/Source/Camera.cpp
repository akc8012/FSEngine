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
	rotation = vec2(0, 0);
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
	const vec3 Up = vec3(0.0f, 1.0f, 0.0f);
	const vec3 Forward = vec3(0.0f, 0.0f, -1.0f);

	vec3 right = glm::normalize(glm::cross(GetDirection(), Up));
	vec3 direction = Forward;

	if (systems->fileSystem->GetSettingsValue<bool>("CameraControl"))
	{
		direction = GetDirectionInput(right, Up) * direction;

		position += GetFloorMovementInput(GetDirection(), right) * GetFrameAdjustedSpeed();
		position.y += GetHeightInput() * GetFrameAdjustedSpeed();
	}

	viewTransform->LookAt(position, position + direction, Up);
}

quat Camera::GetDirectionInput(const vec3& right, const vec3& up)
{
	rotation.x += systems->input->GetDigitalAxis(SDL_SCANCODE_I, SDL_SCANCODE_K) * GetFrameAdjustedSpeed();
	rotation.y += -systems->input->GetDigitalAxis(SDL_SCANCODE_L, SDL_SCANCODE_J) * GetFrameAdjustedSpeed();
	SetDebugText(TransformComponent::GetVectorString(rotation));

	quat pitchRotation = glm::angleAxis(rotation.x, right);
	quat yawRotation = glm::angleAxis(rotation.y, up);

	return pitchRotation * yawRotation;
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

vec3 Camera::GetDirection() const
{
	return -1.f * vec3(viewTransform->GetMatrix()[0][2], viewTransform->GetMatrix()[1][2], viewTransform->GetMatrix()[2][2]);
}
