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
	void CalculateViewMatrix(float deltaTime);
	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

public:
	Camera();
	void Update(float deltaTime);
};
