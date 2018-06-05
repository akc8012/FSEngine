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

	const char* vertexShaderSource = {
		"#version 140\n"
		"in vec3 vertexPos;"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0);\n"
		"}\n"
	};

	const char* fragmentShaderSource = {
		"#version 140\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n"
	};

	unsigned int vertexShaderId = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShaderId = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	int success;
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
		throw (string)"Error linking program " + to_string(programId);

	return programId;
}

unsigned int Renderer::createShader(unsigned int type, const char* source)
{
	unsigned int shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, NULL);

	int success;
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
		throw (string)"Unable to compile shader " + to_string(shaderId);

	return shaderId;
}

void Renderer::setBuffers()
{
	vertexPosId = glGetAttribLocation(programId, "vertexPos");
	if (vertexPosId == -1)
		throw (string)"vertexPos is not a valid glsl program variable!";

	glClearColor(0, 0.5f, 1, 1);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indexData[] = { 0, 1, 2, 3 };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

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
	glEnableVertexAttribArray(vertexPosId);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vertexPosId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPosId);

	//Unbind program
	glUseProgram(NULL);

	//Update screen
	SDL_GL_SwapWindow(window);
}

Renderer::~Renderer()
{
	glDeleteProgram(programId);
}
