#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include <SDL.h>

class Renderer
{
private:
	SDL_GLContext context;
	ShaderProgram* shaderProgram = NULL;
	unsigned int vertexArrayId = 0;

	Texture* brickTexture = NULL;
	Texture* awesomefaceTexture = NULL;

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize;
		int stride;
		int offset;
	};

	SDL_GLContext createContext(SDL_Window* window);
	unsigned int createVertexArray();

	void sendVertices(unsigned int vertexBufferId);
	void sendIndices(unsigned int elementBufferId);

	void sendPositionAttribute();
	void sendColorAttribute();
	void sendTextureAttribute();
	void sendVertexAttribute(const VertexAttribute& attribute);

	void rotateContainer();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
	void rebuildShaderProgram();
};
