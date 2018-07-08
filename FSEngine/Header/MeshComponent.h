#pragma once
#include "Component.h"
#include "Vertex.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
using namespace glm;

#include <vector>
using std::vector;

class MeshComponent : public Component
{
private:
	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride = sizeof(Vertex);
		size_t offset;
	};

	vector<Vertex> vertices;
	vector<Uint32> indices;

	Uint32 vertexArrayId = NULL;

	void CreateVertexArray();

	void SendVertices(Uint32 vertexBufferId);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute();
	void SendNormalAttribute();
	void SendTextureAttribute();

	void SendVertexAttribute(const VertexAttribute& attribute);

public:
	MeshComponent(const vector<Vertex>& vertices, const vector<Uint32>& indices);
	void BindVertexArray();

	const type_info& GetType() const;
};
