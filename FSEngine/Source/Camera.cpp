#include "../Header/Camera.h"

Camera::Camera(Window* window)
 : window(window)
{

}

void Camera::Start()
{
	ResetViewTransform();

	components->transform->Add(GetName(), make_shared<Transform>(), "View");
	components->transform->Add(GetName(), make_shared<Transform>(), "Perspective");
	components->transform->Add(GetName(), make_shared<Transform>(), "Orthographic");

	GetParameterCollection()->SetParameter(GameObject::DoLateUpdate, true);
	GetParameterCollection()->SetParameter(GameObject::DoDraw, false);

	cursorRay.origin = position;

	systems->eventSystem->AddListener(this);
}

void Camera::ResetViewTransform()
{
	SetPosition(vec3(0, 1.5f, 5));
	SetOrientation(vec3(0, -90, 0));
}

void Camera::ReceiveEvent(const string& name, const json& event)
{
	if (name == "CameraPosition")
		position = vec3(event[0], event[1], event[2]);
}

void Camera::Update()
{
	vec3 forward;
	if (systems->fileSystem->GetSettingsValue<bool>("EditorMode"))
	{
		if (systems->input->IsButtonPressed(SDL_SCANCODE_P))
			ResetViewTransform();

		HandleDirection();
		forward = FSMath::EulerAngleToDirectionVector(direction);
		HandlePosition(forward);
	}
	else
		forward = FSMath::EulerAngleToDirectionVector(direction);

	mat4 viewMatrix = CalculateViewMatrix(forward);
	GetComponent<Transform>("View")->SetMatrix(viewMatrix);

	mat4 perspectiveMatrix = CalculateProjectionMatrixPerspective();
	GetComponent<Transform>("Perspective")->SetMatrix(perspectiveMatrix);

	mat4 orthographicMatrix = CalculateProjectionMatrixOrthographic();
	GetComponent<Transform>("Orthographic")->SetMatrix(orthographicMatrix);
}

#pragma region Handle Input
void Camera::HandleDirection()
{
	direction += GetDirectionDelta();
	direction.x = ClampPitch(direction.x);
}

vec3 Camera::GetDirectionDelta() const
{
	return GetDirectionMouseInput() + (GetDirectionKeyInput() * GetFrameAdjustedSpeed());
}

vec3 Camera::GetDirectionMouseInput() const
{
	if (!(systems->input->IsButtonHeld(SDL_SCANCODE_LALT) && systems->input->IsButtonHeld(SDL_BUTTON_LEFT)))
		return FSMath::Zero;

	vec2 currentDevicePosition = GetDeviceNormalizedCursorPosition(systems->input->GetCursorPosition());
	vec2 lastDevicePosition = GetDeviceNormalizedCursorPosition(systems->input->GetLastCursorPosition());

	vec2 cursorDelta = currentDevicePosition - lastDevicePosition;
	float pitchInputValue = -cursorDelta.y;
	float yawInputValue = -cursorDelta.x;

	return vec3(glm::degrees(pitchInputValue), glm::degrees(yawInputValue), 0);
}

vec3 Camera::GetDirectionKeyInput() const
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

void Camera::HandlePosition(const vec3& forward)
{
	cursorRay.direction = ProjectCursorPositionToWorldDirection();
	vec3 cursorPosition = GetCursorPositionAtRayIntersect();
	if (!systems->input->IsButtonHeld(SDL_BUTTON_MIDDLE))
		cursorRay.origin = position;

	position += GetPositionDelta(forward, cursorPosition);
	lastCursorPosition = cursorPosition;
}

vec3 Camera::GetPositionDelta(const vec3& forward, const vec3& cursorPosition) const
{
	vec3 position = FSMath::Zero;
	vec3 right = glm::normalize(glm::cross(forward, FSMath::Up));

	position += GetPositionMouseInput(cursorPosition) + (GetPositionKeyInput(right, forward) * GetFrameAdjustedSpeed());
	position.y += GetHeightKeyboardInput() * GetFrameAdjustedSpeed();

	float mouseScrollSpeed = systems->fileSystem->GetSettingsValue<float>("CameraScrollSpeed");
	if (!systems->input->IsButtonHeld(SDL_SCANCODE_LALT))
		position += GetZoomInput(forward) * mouseScrollSpeed;
	else
		position.y += GetHeightMouseInput() * mouseScrollSpeed;

	return position;
}

vec3 Camera::GetPositionMouseInput(const vec3& cursorPosition) const
{
	if (!systems->input->IsButtonHeld(SDL_BUTTON_MIDDLE))
		return FSMath::Zero;

	return -(cursorPosition - lastCursorPosition);
}

vec3 Camera::GetPositionKeyInput(const vec3& right, const vec3& forward) const
{
	vec2 inputDelta = vec2(systems->input->GetHorizontalAxis(), -systems->input->GetVerticalAxis());

	vec3 horizontalMovement = inputDelta.x * right;
	vec3 verticalMovement = inputDelta.y * glm::normalize(vec3(forward.x, 0, forward.z));

	return verticalMovement + horizontalMovement;
}

vec3 Camera::GetCursorPositionAtRayIntersect() const
{
	return cursorRay.origin + (cursorRay.direction * GetRayIntersectFloorDistance(cursorRay));
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
#pragma endregion

#pragma region Calculate Matrices
mat4 Camera::CalculateViewMatrix(const vec3& forward) const
{
	return glm::lookAt(position, position + forward, FSMath::Up);
}

mat4 Camera::CalculateProjectionMatrixPerspective() const
{
	vec2 windowSize = window->GetWindowSize();

	const float FieldOfView = glm::radians(45.0f);
	const float AspectRatio = windowSize.x / windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;

	return glm::perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}

mat4 Camera::CalculateProjectionMatrixOrthographic() const
{
	const float Left = -1.0f;
	const float Right = 1.0f;
	const float Bottom = Left;
	const float Top = Right;

	return glm::ortho(Left, Right, Bottom, Top);
}
#pragma endregion

#pragma region Ray Casting
// http://antongerdelan.net/opengl/raycasting.html
vec3 Camera::ProjectCursorPositionToWorldDirection() const
{
	vec4 deviceNormalizedCursorPosition = vec4(GetDeviceNormalizedCursorPosition(systems->input->GetCursorPosition()), -1, 1);
	
	mat4 projectionMatrix = GetComponent<Transform>("Perspective")->GetMatrix();
	vec4 eyeDirection = vec4(vec2(glm::inverse(projectionMatrix) * deviceNormalizedCursorPosition), -1, 0);

	mat4 viewMatrix = GetComponent<Transform>("View")->GetMatrix();
	vec3 worldDirection = glm::normalize(glm::inverse(viewMatrix) * eyeDirection);

	return worldDirection;
}

vec2 Camera::GetDeviceNormalizedCursorPosition(const tvec2<int>& cursorPosition) const
{
	vec2 cursorCoordinates = (vec2)cursorPosition /= (vec2)window->GetWindowSize();
	cursorCoordinates = (cursorCoordinates - 0.5f) * 2.f;
	cursorCoordinates.y = -cursorCoordinates.y;

	return cursorCoordinates;
}

// http://antongerdelan.net/opengl/raycasting.html
float Camera::GetRayIntersectFloorDistance(const ray& ray) const
{
	plane floorPlane(FSMath::Zero, glm::abs(FSMath::Up));
	vec3 vector = -( ((ray.origin * floorPlane.normal) - floorPlane.origin) / (ray.direction * floorPlane.normal) );
	vector = FSMath::NanToZero(vector);

	return glm::dot(floorPlane.normal, vector);
}
#pragma endregion

void Camera::SetPosition(const vec3& position)
{
	this->position = position;
}

vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::SetOrientation(const vec3& direction)
{
	this->direction = direction;
}

vec3 Camera::GetOrientation() const
{
	return direction;
}
