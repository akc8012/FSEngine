#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Window.h"

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

	void CalculateViewMatrix(float deltaTime);
	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

public:
	Camera(Window* window);
	void Update(float deltaTime);

	void SetPosition(const vec3& position);
	vec3 GetPosition() const;
};
