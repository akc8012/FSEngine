#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include "ShaderProgram.h"

#define uint unsigned int

class Renderer
{
private:
	SDL_GLContext context;
	ShaderProgram* shaderProgram = NULL;
	uint vertexArrayId = 0;

	uint createVertexArray();
	void sendVertices(uint vertexBufferId);
	void sendIndices(uint elementBufferId);
	void sendVertexAttributes(uint length);
	void unbindVertexObjects();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
};
