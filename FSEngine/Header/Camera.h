#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Window.h"
#include "RenderText.h"

class Camera : public GameObject
{
private:
	TransformComponent* viewTransform = nullptr;
	Window* window = nullptr;

	vec3 position;
	vec3 direction;

	void ResetViewTransform();

	void CalculateViewMatrix();
	vec3 HandleInput();

	vec3 GetDirectionInput() const;
	float ClampPitch(float pitch) const;
	vec3 GetFloorMovementInput(const vec3& right, const vec3& forward) const;
	float GetHeightKeyboardInput() const;
	float GetHeightMouseInput() const;

	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

	float GetFrameAdjustedSpeed() const;
	void SetDebugText(const string& text) const;

public:
	Camera(Window* window);

	void Update() override;

	void SetPosition(const vec3& position);
	void SetDirection(const vec3& direction);
	vec3 GetPosition() const;
	vec3 GetDirection() const;
};
