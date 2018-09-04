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
	vec2 rotation;

	void ResetViewTransform();

	void CalculateViewMatrix();
	quat GetDirectionInput(const vec3& right, const vec3& up);
	vec3 GetFloorMovementInput(const vec3& forward, const vec3& right) const;
	float GetHeightInput() const;

	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

	float GetFrameAdjustedSpeed() const;
	void SetDebugText(const string& text) const;

public:
	Camera(Window* window);

	void Update() override;

	void SetPosition(const vec3& position);
	vec3 GetPosition() const;
	vec3 GetDirection() const;
};
