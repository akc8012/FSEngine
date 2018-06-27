#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Window.h"

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>
using namespace std;

class Camera : public GameObject
{
private:
	Window* window = NULL;
	mat4 viewMatrix = mat4(1.0f);
	mat4 projectionMatrix = mat4(1.0f);
	vec3 position = vec3(0, 0, 3);

	void CalculateViewMatrix(Uint32 deltaTime);
	void CalculateProjectionMatrix();

public:
	Camera(Window* window);

	void Update(Uint32 deltaTime);

	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
};