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
	mat4 projectionMatrix = mat4(1.0f);

	void CalculateViewMatrix(Uint32 deltaTime);
	void CalculateProjectionMatrixPerspective();
	void CalculateProjectionMatrixOrthographic();

public:
	Camera(FileSystem* fileSystem, Window* window);
	void Update(Uint32 deltaTime);

	mat4 GetProjectionMatrix() const;
};
