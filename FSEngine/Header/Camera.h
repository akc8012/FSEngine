#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Window.h"

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>

class Camera : public GameObject
{
private:
	Window* window = nullptr;
	mat4 projectionPerspective = mat4(1.0f);
	mat4 projectionOrthographic = mat4(1.0f);

	void CalculateViewMatrix(float deltaTime);
	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

public:
	Camera(FileSystem* fileSystem, Input* input, Window* window);
	void Update(float deltaTime);

	mat4 GetProjectionPerspective() const;
	mat4 GetProjectionOrthographic() const;
};
