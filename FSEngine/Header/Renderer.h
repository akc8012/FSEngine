#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "Window.h"
#include "Timer.h"
#include "GameObject.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
using namespace std;

class Renderer
{
private:
	ShaderProgram* shaderProgram = NULL;

	void ClearScreen();
	void DrawTriangles();

	void SetViewMatrix(mat4 viewMatrix);
	void SetProjectionMatrix(vec2 windowSize);
	void SetFragmentMixUniforms();

public:
	Renderer(ShaderProgram* shaderProgram);
	~Renderer();

	void StartRender();
	void RenderGameObject(GameObject* gameObject);
	void EndRender(Window* window, mat4 viewMatrix);

	void RecompileShaders();
};
