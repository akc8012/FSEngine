#pragma once
#include "Component.h"
#include "TextureComponent.h"

#include <glm\glm.hpp>
using namespace glm;

#include <vector>
using std::vector;

class MeshComponent : public Component
{
private:
	struct Vertex
	{
		vec3 position;
		vec3 normal;
		vec2 textureCoord;
	};

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
	vector<TextureComponent> textures;

	Uint32 vertexArrayId = NULL;

	void CreateVertexArray();

	void SendVertices(Uint32 vertexBufferId);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute();
	void SendNormalAttribute();
	void SendTextureAttribute();

	void SendVertexAttribute(const VertexAttribute& attribute);

public:
	MeshComponent(const vector<Vertex>& vertices, const vector<unsigned int>& indices, const vector<TextureComponent>& textures);
	void BindVertexArray();

	const type_info& GetType() const;
};
