#include "../Header/Renderer.h"
#include "../Header/Input.h"
#include "../Header/Timer.h"
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <string>
using namespace std;

Renderer::Renderer(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;

	CreateVertexArray();
	SetFragmentMixUniforms();

	brickTexture = new Texture("Resource/Image/wall.png");
	awesomefaceTexture = new Texture("Resource/Image/awesomeface.png");
}

void Renderer::CreateVertexArray()
{
	unsigned int vertexBufferId, elementBufferId;
	const int Amount = 1;
	glGenVertexArrays(Amount, &vertexArrayId);
	glGenBuffers(Amount, &vertexBufferId);
	glGenBuffers(Amount, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	SendVertices(vertexBufferId);
	SendIndices(elementBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(Amount, &elementBufferId);
	glDeleteBuffers(Amount, &vertexBufferId);
}

void Renderer::SendVertices(unsigned int vertexBufferId)
{
	float vertices[] =
	{
		 // positions         // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	SendPositionAttribute();
	SendTextureAttribute();
}

void Renderer::SendPositionAttribute()
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.stride = 5;
	positionAttribute.offset = 0;

	SendVertexAttribute(positionAttribute);
}

void Renderer::SendTextureAttribute()
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 1;
	textureAttribute.size = 2;
	textureAttribute.stride = 5;
	textureAttribute.offset = 3;

	SendVertexAttribute(textureAttribute);
}

void Renderer::SendVertexAttribute(const VertexAttribute& attribute)
{
	glVertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, attribute.normalize, attribute.stride * sizeof(float), (void*)(attribute.offset * sizeof(float)));
	glEnableVertexAttribArray(attribute.location);
}

void Renderer::SendIndices(unsigned int elementBufferId)
{
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Renderer::SetFragmentMixUniforms()
{
	shaderProgram->Use();

	int uniformValue = 0;
	shaderProgram->SetInt("texture1", uniformValue);
	shaderProgram->SetInt("texture2", uniformValue+1);
}

void Renderer::Render(Window* window)
{
	ClearScreen();

	shaderProgram->Use();
	BindTextures();
	glBindVertexArray(vertexArrayId);

	SetModelMatrix();
	SetViewMatrix();
	SetProjectionMatrix(window->GetWindowSize());

	DrawTriangles();

	window->SwapWindow();
}

void Renderer::ClearScreen()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::BindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture->GetId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, awesomefaceTexture->GetId());
}

void Renderer::SetModelMatrix()
{
	float angle = Timer::GetSeconds() * radians(50.0f);
	const vec3 Axis = vec3(0.5f, 1.0f, 0.0f);
	mat4 transform = rotate(mat4(1.0f), angle, Axis);

	shaderProgram->SetMatrix("model", transform);
}

void Renderer::SetViewMatrix()
{
	vec3 forwardVector = vec3(0.0f, 0.0f, -1.0f);
	vec3 upVector = vec3(0.0f, 1.0f, 0.0f);

	cameraPosition += normalize(cross(forwardVector, upVector)) * Input::GetHorizontalAxis();
	cameraPosition += -Input::GetVerticalAxis() * forwardVector;

	mat4 view = lookAt(cameraPosition, cameraPosition + forwardVector, upVector);
	shaderProgram->SetMatrix("view", view);
}

void Renderer::SetProjectionMatrix(vec2 windowSize)
{
	const float FieldOfView = radians(45.0f);
	const float AspectRatio = (float)windowSize.x / (float)windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;
	mat4 projectionMatrix = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);

	shaderProgram->SetMatrix("projection", projectionMatrix);
}

void Renderer::DrawTriangles()
{
	const int First = 0, Count = 36;
	glDrawArrays(GL_TRIANGLES, 0, Count);
}

void Renderer::RecompileShaders()
{
	shaderProgram->CreateShaders();
	SetFragmentMixUniforms();
}

Renderer::~Renderer()
{
	delete brickTexture;
	delete awesomefaceTexture;

	const int Amount = 1;
	glDeleteVertexArrays(Amount, &vertexArrayId);
}
