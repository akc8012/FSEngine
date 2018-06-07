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

	shaderProgram = new ShaderProgram();
	vertexArrayId = createVertexArray();
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

	glUseProgram(shaderProgram->getShaderProgramId());
	glBindVertexArray(vertexArrayId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(window);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayId);
	delete shaderProgram;
}
