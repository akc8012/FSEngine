#pragma once
#include "ShaderProgram.h"
#include <SDL.h>

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
