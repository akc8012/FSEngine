#pragma once
#include "ShaderProgram.h"
#include <SDL.h>

#define uint unsigned int

class Renderer
{
private:
	SDL_GLContext context;
	ShaderProgram* shaderProgram = NULL;
	uint vertexArrayId = 0;

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize;
		int stride;
		int offset;
	};

	SDL_GLContext createContext(SDL_Window* window);
	uint createVertexArray();

	void sendVertices(uint vertexBufferId);
	void sendIndices(uint elementBufferId);

	void sendPositionAttribute();
	void sendColorAttribute();
	void sendTextureAttribute();
	void sendVertexAttribute(const VertexAttribute& attribute);

	void unbindVertexObjects();

public:
	Renderer(SDL_Window* window);
	~Renderer();

	void render(SDL_Window* window);
	void rebuildShaderProgram();
};
