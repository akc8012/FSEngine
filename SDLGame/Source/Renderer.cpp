#include "../Header/Renderer.h"
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <string>
using namespace std;

Renderer::Renderer(SDL_Window* window)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = createContext(window);

	glewExperimental = GL_TRUE;
	uint glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);

	if (SDL_GL_SetSwapInterval(1) < 0)
		throw (string)"Warning: Unable to set VSync! SDL Error: " + SDL_GetError();

	shaderProgram = new ShaderProgram();
	vertexArrayId = createVertexArray();

	brickTexture = new Texture("Resource/Image/wall.png");
}

SDL_GLContext Renderer::createContext(SDL_Window* window)
{
	SDL_GL_DeleteContext(context);
	context = SDL_GL_CreateContext(window);
	if (context == NULL)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();

	return context;
}

uint Renderer::createVertexArray()
{
	uint vertexBufferId, elementBufferId;
	//to-do: clarify all this stuff
	glGenVertexArrays(1, &vertexArrayId);
	glGenBuffers(1, &vertexBufferId);
	glGenBuffers(1, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	sendVertices(vertexBufferId);
	sendIndices(elementBufferId);

	unbindVertexObjects();
	glDeleteBuffers(1, &elementBufferId);
	glDeleteBuffers(1, &vertexBufferId);

	return vertexArrayId;
}

void Renderer::sendVertices(uint vertexBufferId)
{
	float vertices[] =
	{
		 // positions         // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	sendPositionAttribute();
	sendColorAttribute();
	sendTextureAttribute();
}

void Renderer::sendPositionAttribute()
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.normalize = false;
	positionAttribute.stride = 8 * sizeof(float);
	positionAttribute.offset = 0;

	sendVertexAttribute(positionAttribute);
}

void Renderer::sendColorAttribute()
{
	VertexAttribute colorAttribute;
	colorAttribute.location = 1;
	colorAttribute.size = 3;
	colorAttribute.normalize = false;
	colorAttribute.stride = 8 * sizeof(float);
	colorAttribute.offset = 3;

	sendVertexAttribute(colorAttribute);
}

void Renderer::sendTextureAttribute()
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 2;
	textureAttribute.size = 3;
	textureAttribute.normalize = false;
	textureAttribute.stride = 8 * sizeof(float);
	textureAttribute.offset = 6;

	sendVertexAttribute(textureAttribute);
}

void Renderer::sendVertexAttribute(const VertexAttribute& attribute)
{
	glVertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, attribute.normalize, attribute.stride, (void*)(attribute.offset * sizeof(float)));
	glEnableVertexAttribArray(attribute.location);
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
	glBindTexture(GL_TEXTURE_2D, brickTexture->getTextureId());
	glBindVertexArray(vertexArrayId);

	const int Count = 6, Indices = 0;
	glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, Indices);

	SDL_GL_SwapWindow(window);
}

void Renderer::rebuildShaderProgram()
{
	shaderProgram->createShaderProgram();
}

Renderer::~Renderer()
{
	delete brickTexture;
	glDeleteVertexArrays(1, &vertexArrayId);
	delete shaderProgram;
	SDL_GL_DeleteContext(context);
}
