#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Renderer
{
private:
	SDL_GLContext context;
	ShaderProgram* shaderProgram = NULL;
	unsigned int vertexArrayId = 0;

	Texture* brickTexture = NULL;
	Texture* awesomefaceTexture = NULL;

	vec3 cubePosition;

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride;
		int offset;
	};

	SDL_GLContext createContext(SDL_Window* window);
	unsigned int createVertexArray();

	void sendVertices(unsigned int vertexBufferId);
	void sendIndices(unsigned int elementBufferId);

	void sendPositionAttribute();
	void sendTextureAttribute();
	void sendVertexAttribute(const VertexAttribute& attribute);

	void clearScreen();
	void bindTextures();
	void drawTriangles();

	void setModelMatrix();
	void setViewMatrix();
	void setProjectionMatrix(SDL_Window* window);
	void setFragmentMixUniforms();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
	void recompileShaders();
};
