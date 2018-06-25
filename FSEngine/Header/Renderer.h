#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "Window.h"
#include "Timer.h"
#include "TransformComponent.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
using namespace std;

class Renderer
{
private:
	ShaderProgram* shaderProgram = NULL;
	Uint32 vertexArrayId = 0;

	Texture* brickTexture = NULL;
	Texture* awesomefaceTexture = NULL;

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride;
		int offset;
	};

	void CreateVertexArray();
	void SendVertices(Uint32 vertexBufferId);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute();
	void SendTextureAttribute();
	void SendVertexAttribute(const VertexAttribute& attribute);

	void ClearScreen();
	void BindTextures();
	void DrawTriangles();

	void SetModelMatrix();
	void SetViewMatrix(mat4 viewMatrix);
	void SetProjectionMatrix(vec2 windowSize);
	void SetFragmentMixUniforms();

public:
	Renderer(ShaderProgram* shaderProgram);
	~Renderer();

	void Render(Window* window, mat4 viewMatrix);
	void RecompileShaders();
};
