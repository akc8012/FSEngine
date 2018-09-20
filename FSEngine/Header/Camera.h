#pragma once
#include "GameObject.h"
#include "Window.h"
#include "RenderText.h"

class Camera : public GameObject
{
private:
	GameObject* point = nullptr;

	TransformComponent* viewTransform = nullptr;
	Window* window = nullptr;

	vec3 position;
	vec3 direction;

	void ResetViewTransform();

	mat4 CalculateViewMatrix(const vec3& forward) const;
	mat4 CalculateProjectionMatrixPerspective() const;
	mat4 CalculateProjectionMatrixOrthographic() const;

	vec3 HandleInput();

	vec3 GetDirectionInput() const;
	vec3 GetFloorMovementInput(const vec3& right, const vec3& forward) const;

	vec3 GetZoomInput(const vec3& forward) const;
	float GetHeightKeyboardInput() const;
	float GetHeightMouseInput() const;

	float ClampPitch(float pitch) const;

	vec3 ProjectCursorPositionToWorldDirection(const mat4& projectionMatrix, const mat4& viewMatrix) const;
	vec2 GetDeviceNormalizedCursorPosition() const;
	float GetRayIntersectFloorDistance(const ray& ray) const;

	float GetFrameAdjustedSpeed() const;
	void SetDebugText(const string& text) const;

public:
	Camera(Window* window);

	void Start() override;
	void Update() override;

	void SetPosition(const vec3& position);
	void SetDirection(const vec3& direction);
	vec3 GetPosition() const;
	vec3 GetDirection() const;
};
