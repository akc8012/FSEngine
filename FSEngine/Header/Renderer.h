#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "Window.h"
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Renderer
{
private:
	ShaderProgram* shaderProgram = NULL;
	unsigned int vertexArrayId = 0;

	Texture* brickTexture = NULL;
	Texture* awesomefaceTexture = NULL;

	vec3 cameraPosition = vec3(0, 0, 3);

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride;
		int offset;
	};

	void CreateVertexArray();
	void SendVertices(unsigned int vertexBufferId);
	void SendIndices(unsigned int elementBufferId);

	void SendPositionAttribute();
	void SendTextureAttribute();
	void SendVertexAttribute(const VertexAttribute& attribute);

	void ClearScreen();
	void BindTextures();
	void DrawTriangles();

	void SetModelMatrix();
	void SetViewMatrix();
	void SetProjectionMatrix(vec2 windowSize);
	void SetFragmentMixUniforms();

public:
	Renderer(ShaderProgram* shaderProgram);
	~Renderer();

	void Render(Window* window);
	void RecompileShaders();
};
