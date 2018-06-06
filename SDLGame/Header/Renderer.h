#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#define uint unsigned int

class Renderer
{
private:
	SDL_GLContext context;

	uint shaderProgramId = 0;
	uint vertexArrayId = 0;

	uint createShaderProgram();
	uint createVertexShader();
	uint createFragmentShader();
	uint createShader(uint type, const char* source);

	uint createVertexArray();
	void unbindVertexObjects(uint vertexBufferId);
	void sendVertices();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
};
