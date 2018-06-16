#include "../Header/Renderer.h"
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

Renderer::Renderer(SDL_Window* window)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = createContext(window);

	glewExperimental = GL_TRUE;
	unsigned int glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);

	const int Interval = 1;
	if (SDL_GL_SetSwapInterval(Interval) == -1)
		throw (string)"Warning: Unable to set VSync! SDL Error: " + SDL_GetError();

	shaderProgram = new ShaderProgram();
	vertexArrayId = createVertexArray();

	shaderProgram->use();
	setFragmentMixUniforms();

	brickTexture = new Texture("Resource/Image/wall.png");
	awesomefaceTexture = new Texture("Resource/Image/awesomeface.png");
}

SDL_GLContext Renderer::createContext(SDL_Window* window)
{
	SDL_GL_DeleteContext(context);
	context = SDL_GL_CreateContext(window);
	if (context == NULL)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();

	return context;
}

unsigned int Renderer::createVertexArray()
{
	unsigned int vertexBufferId, elementBufferId;
	const int Amount = 1;
	glGenVertexArrays(Amount, &vertexArrayId);
	glGenBuffers(Amount, &vertexBufferId);
	glGenBuffers(Amount, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	sendVertices(vertexBufferId);
	sendIndices(elementBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(Amount, &elementBufferId);
	glDeleteBuffers(Amount, &vertexBufferId);

	return vertexArrayId;
}

void Renderer::sendVertices(unsigned int vertexBufferId)
{
	float vertices[] =
	{
		 // positions         // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	sendPositionAttribute();
	sendTextureAttribute();
}

void Renderer::sendPositionAttribute()
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.stride = 5 * sizeof(float);
	positionAttribute.offset = 0;

	sendVertexAttribute(positionAttribute);
}

void Renderer::sendTextureAttribute()
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 1;
	textureAttribute.size = 2;
	textureAttribute.stride = 5 * sizeof(float);
	textureAttribute.offset = 3;

	sendVertexAttribute(textureAttribute);
}

void Renderer::sendVertexAttribute(const VertexAttribute& attribute)
{
	glVertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, attribute.normalize, attribute.stride, (void*)(attribute.offset * sizeof(float)));
	glEnableVertexAttribArray(attribute.location);
}

void Renderer::sendIndices(unsigned int elementBufferId)
{
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Renderer::setFragmentMixUniforms()
{
	int uniformValue = 0;
	shaderProgram->setInt("texture1", uniformValue);
	shaderProgram->setInt("texture2", uniformValue+1);
}

void Renderer::render(SDL_Window* window)
{
	clearScreen();

	shaderProgram->use();
	bindTextures();
	glBindVertexArray(vertexArrayId);

	setModelMatrix();
	setViewMatrix();
	setProjectionMatrix(window);

	drawTriangles();

	SDL_GL_SwapWindow(window);
}

void Renderer::clearScreen()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::bindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture->getId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, awesomefaceTexture->getId());
}

void Renderer::setModelMatrix()
{
	const float Angle = radians(-55.0f);
	const vec3 Axis = vec3(1.0f, 0.0f, 0.0f);
	mat4 modelMatrix = rotate(mat4(1.0f), Angle, Axis);
	shaderProgram->setMatrix("model", modelMatrix);
}

void Renderer::setViewMatrix()
{
	mat4 viewMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
	shaderProgram->setMatrix("view", viewMatrix);
}

void Renderer::setProjectionMatrix(SDL_Window* window)
{
	const float FieldOfView = radians(45.0f);
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	const float AspectRatio = (float)width / (float)height;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;
	mat4 projectionMatrix = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
	shaderProgram->setMatrix("projection", projectionMatrix);
}

void Renderer::drawTriangles()
{
	const int Count = 6, Indices = 0;
	glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, Indices);
}

void Renderer::recompileShaders()
{
	shaderProgram->createShaders();
	setFragmentMixUniforms();
}

Renderer::~Renderer()
{
	delete brickTexture;
	delete awesomefaceTexture;
	delete shaderProgram;

	const int Amount = 1;
	glDeleteVertexArrays(Amount, &vertexArrayId);
	SDL_GL_DeleteContext(context);
}
