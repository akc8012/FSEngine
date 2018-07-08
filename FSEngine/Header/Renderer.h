#pragma once
#include "ShaderProgram.h"
#include "Window.h"
#include "GameObject.h"
#include "Model.h"
#include "Camera.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

#include <string>

class Renderer
{
private:
	Window* window = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Camera* camera = nullptr;

	void ClearScreen();
	void SetCameraMatrices();

	void DrawTriangleArrays(Uint32 verticeCount);
	void DrawTriangleElements(Uint32 indiceCount);

public:
	Renderer(FileSystem* fileSystem, Window* window, ShaderProgram* shaderProgram, Input* input);
	~Renderer();

	void StartRender(float deltaTime);
	void RenderGameObject(GameObject* gameObject);
	void RenderModel(Model* model);
	void EndRender();
};
