#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

class OpenGL
{
private:
	SDL_GLContext context;

	GLuint programId = 0;
	GLint vertexPos2DLocation = -1;
	GLuint vbo = 0;
	GLuint ebo = 0;

	GLuint createProgram();
	void createVertexShader(GLuint programId);
	void createFragmentShader(GLuint programId);
	void setBuffers();

public:
	OpenGL(SDL_Window* window);
	~OpenGL();

	void render(SDL_Window* window);
};
