#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Window.h"
#include "RenderText.h"

#include <SDL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
using namespace glm;

#include <vector>

class Camera : public GameObject
{
private:
	TransformComponent* viewTransform = nullptr;
	Window* window = nullptr;

	vec3 position;
	vec3 direction;

	void ResetViewTransform();

	void CalculateViewMatrix();
	vec3 GetDirectionInput() const;
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

	void SetDirection(const vec3& direction);
	vec3 GetDirection() const;
};
