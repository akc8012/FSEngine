#include "../Header/Renderer.h"
#include <string>
using namespace std;

Renderer::Renderer(SDL_Window* window)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = SDL_GL_CreateContext(window);
	if (context == NULL)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();

	glewExperimental = GL_TRUE;
	uint glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);

	if (SDL_GL_SetSwapInterval(1) < 0)
		throw (string)"Warning: Unable to set VSync! SDL Error: " + SDL_GetError();

	shaderProgramId = createShaderProgram();
	vertexArrayId = createVertexArray();
}

uint Renderer::createShaderProgram()
{
	shaderProgramId = glCreateProgram();

	uint vertexShaderId = createVertexShader();
	glAttachShader(shaderProgramId, vertexShaderId);

	uint fragmentShaderId = createFragmentShader();
	glAttachShader(shaderProgramId, fragmentShaderId);

	int success;
	glLinkProgram(shaderProgramId);
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		throw (string)"Error linking program: " + infoLog;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return shaderProgramId;
}

uint Renderer::createVertexShader()
{
	const char* vertexShaderSource = {
		"#version 330 core\n"
		"layout (location = 0) in vec3 vertexPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0);\n"
		"}\n"
	};

	return createShader(GL_VERTEX_SHADER, vertexShaderSource);
}

uint Renderer::createFragmentShader()
{
	const char* fragmentShaderSource = {
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n"
	};

	return createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
}

uint Renderer::createShader(uint type, const char* source)
{
	uint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, NULL);

	int success;
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		throw (string)"Unable to compile shader: " + infoLog;
	}

	return shaderId;
}

uint Renderer::createVertexArray()
{
	uint vertexBufferId, elementBufferId;
	glGenVertexArrays(1, &vertexArrayId);
	glGenBuffers(1, &vertexBufferId);
	glGenBuffers(1, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	sendVertices(vertexBufferId);
	sendIndices(elementBufferId);
	sendVertexAttributes(3);

	unbindVertexObjects();
	glDeleteBuffers(1, &elementBufferId);
	glDeleteBuffers(1, &vertexBufferId);

	return vertexArrayId;
}

void Renderer::sendVertices(uint vertexBufferId)
{
	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::sendIndices(uint elementBufferId)
{
	uint indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Renderer::sendVertexAttributes(uint length)
{
	glVertexAttribPointer(0, length, GL_FLOAT, false, length * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::unbindVertexObjects()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::render(SDL_Window* window)
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgramId);
	glBindVertexArray(vertexArrayId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(window);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayId);
	glDeleteProgram(shaderProgramId);
}
