#pragma once
#include "ShaderProgram.h"
#include "Window.h"
#include "GameObject.h"
#include "Camera.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
#include <map>
using namespace std;

class Renderer
{
private:
	Window* window = NULL;
	ShaderProgram* shaderProgram = NULL;
	GameObject* camera = NULL;

	map<string, Uint32> uniformLocations; //to-do: we shouldn't be storing all of this here

	void SetFragmentMixUniforms();

	void ClearScreen();
	void DrawTriangles();

public:
	Renderer(Window* window, ShaderProgram* shaderProgram);
	~Renderer();

	void StartRender();
	void RenderGameObject(GameObject* gameObject);
	void EndRender(Uint32 deltaTime);

	void RecompileShaders();
};
