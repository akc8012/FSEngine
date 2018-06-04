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
	int vertexPos2DLocation = -1;
	unsigned int vbo = 0;
	unsigned int ebo = 0;

	GLuint createProgram();
	void createVertexShader(unsigned int programId);
	void createFragmentShader(unsigned int programId);
	void setBuffers();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
};
