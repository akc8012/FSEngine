#include "../Header/Renderer.h"
#include <string>
using namespace std;

Renderer::Renderer(SDL_Window* window)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = SDL_GL_CreateContext(window);
	if (context == NULL)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();

	glewExperimental = GL_TRUE;
	unsigned int glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);

	if (SDL_GL_SetSwapInterval(1) < 0)
		throw (string)"Warning: Unable to set VSync! SDL Error: " + SDL_GetError();

	programId = createProgram();
	setBuffers();
}

GLuint Renderer::createProgram()
{
	programId = glCreateProgram();

	createVertexShader(programId);
	createFragmentShader(programId);
	glLinkProgram(programId);

	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
		throw (string)"Error linking program " + to_string(programId);

	return programId;
}

void Renderer::createVertexShader(unsigned int programId)
{
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};
	glShaderSource(vertexShaderId, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShaderId);

	int success;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
		throw (string)"Unable to compile vertex shader " + to_string(vertexShaderId);

	glAttachShader(programId, vertexShaderId);
}

void Renderer::createFragmentShader(unsigned int programId)
{
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource[] =
	{
		"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
	};
	glShaderSource(fragmentShaderId, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	int success;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
		throw (string)"Unable to compile fragment shader " + to_string(fragmentShaderId);

	glAttachShader(programId, fragmentShaderId);
}

void Renderer::setBuffers()
{
	vertexPos2DLocation = glGetAttribLocation(programId, "LVertexPos2D");
	if (vertexPos2DLocation == -1)
		throw (string)"LVertexPos2D is not a valid glsl program variable!";

	glClearColor(0.f, 0.f, 0.f, 1.f);

	float vertexData[] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f
	};
	unsigned int indexData[] = { 0, 1, 2, 3 };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(float), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned int), indexData, GL_STATIC_DRAW);
}

void Renderer::render(SDL_Window* window)
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind program
	glUseProgram(programId);

	//Enable vertex position
	glEnableVertexAttribArray(vertexPos2DLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPos2DLocation);

	//Unbind program
	glUseProgram(NULL);

	//Update screen
	SDL_GL_SwapWindow(window);
}

Renderer::~Renderer()
{
	glDeleteProgram(programId);
}
