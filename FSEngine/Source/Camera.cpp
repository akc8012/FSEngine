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
	SetPosition(vec3(0, 0, 5));
	SetDirection(vec3(0, -90, 0));
}

void Camera::Update()
{
	if (systems->input->IsButtonPressed(SDL_SCANCODE_P))
		ResetViewTransform();

	CalculateViewMatrix();
	CalculateProjectionMatrixPerspective();
	CalculateProjectionMatrixOrthographic();

	ProjectScreenSpaceToWorldSpace();

	float data;
	tvec2<int> cursor = systems->input->GetCursorPosition();
	cursor.y = std::abs(cursor.y - window->GetWindowSize().y) - 1;

	glReadPixels(cursor.x, cursor.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &data);
}

#pragma region Calculate Matrices
void Camera::CalculateViewMatrix()
{
	vec3 forward = TransformComponent::Forward;

	if (systems->fileSystem->GetSettingsValue<bool>("CameraControl"))
		forward = HandleInput();

	viewTransform->LookAt(position, position + forward, TransformComponent::Up);
}

vec3 Camera::HandleInput()
{
	direction += GetDirectionInput() * GetFrameAdjustedSpeed();
	direction.x = ClampPitch(direction.x);

	vec3 forward = TransformComponent::EulerAngleToDirectionVector(direction);

	vec3 right = glm::normalize(glm::cross(forward, TransformComponent::Up));
	position += GetFloorMovementInput(right, forward) * GetFrameAdjustedSpeed();
	position.y += GetHeightKeyboardInput() * GetFrameAdjustedSpeed();

	float mouseScrollSpeed = systems->fileSystem->GetSettingsValue<float>("CameraScrollSpeed");
	if (!systems->input->IsButtonHeld(SDL_SCANCODE_LALT))
		position += GetZoomInput(forward) * mouseScrollSpeed;
	else
		position.y += GetHeightMouseInput() * mouseScrollSpeed;

	return forward;
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

vec3 Camera::GetFloorMovementInput(const vec3& right, const vec3& forward) const
{
	vec2 inputDelta = vec2(systems->input->GetHorizontalAxis(), -systems->input->GetVerticalAxis());
	if (systems->input->IsButtonHeld(SDL_BUTTON_MIDDLE))
		inputDelta += vec2(-systems->input->GetCursorDelta().x, systems->input->GetCursorDelta().y);

	vec3 horizontalMovement = inputDelta.x * right;
	vec3 verticalMovement = inputDelta.y * glm::normalize(vec3(forward.x, 0, forward.z));

	return verticalMovement + horizontalMovement;
}

vec3 Camera::GetZoomInput(const vec3& forward) const
{
	return forward * GetHeightMouseInput();
}

float Camera::GetHeightKeyboardInput() const
{
	return systems->input->GetDigitalAxis(SDL_SCANCODE_R, SDL_SCANCODE_F);
}

float Camera::GetHeightMouseInput() const
{
	return (float)systems->input->GetMouseWheelScroll();
}

float Camera::GetFrameAdjustedSpeed() const
{
	return systems->fileSystem->GetSettingsValue<float>("CameraMoveSpeed") * systems->gameTimer->GetDeltaTime();
}

void Camera::SetDebugText(const string& text) const
{
	gameObjectContainer->GetGameObjectAs<RenderText>("DebugText")->SetText(text);
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
#pragma endregion

vec3 Camera::ProjectScreenSpaceToWorldSpace() const
{
	vec4 cursorPosition = vec4(GetNormalizedDeviceCursorCoordinates(), -1, 1);

	mat4 projectionMatrix = GetComponent<TransformComponent>("Perspective")->GetMatrix();
	vec4 eyeDirection = glm::inverse(projectionMatrix) * cursorPosition;
	eyeDirection = vec4(eyeDirection.x, eyeDirection.y, -1, 0);

	mat4 viewMatrix = viewTransform->GetMatrix();
	vec3 worldDirection = glm::normalize(glm::inverse(viewMatrix) * eyeDirection);

	printFS(worldDirection);
	return worldDirection;
}

vec2 Camera::GetNormalizedDeviceCursorCoordinates() const
{
	vec2 cursorCoordinates = (vec2)systems->input->GetCursorPosition() /= (vec2)window->GetWindowSize();
	cursorCoordinates = (cursorCoordinates - 0.5f) * 2.f;
	cursorCoordinates.y = -cursorCoordinates.y;

	return cursorCoordinates;
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
