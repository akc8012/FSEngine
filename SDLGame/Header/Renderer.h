#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

class Renderer
{
private:
	SDL_GLContext context;

	unsigned int programId = 0;
	int vertexPosId = -1;
	unsigned int vbo = 0;
	unsigned int ebo = 0;

	GLuint createProgram();
	unsigned int createShader(unsigned int type, const char* source);
	void setBuffers();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
};
