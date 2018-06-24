#pragma once
#include "Component.h"
#include "Texture.h"

class RenderComponent : public Component
{
private:
	Texture* texture = NULL;
	Uint32 vertexArrayId = 0;

	float* vertices;
	Uint32* indices;

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

public:
	RenderComponent(float* vertices, Uint32* indices, const char* textureFilepath);
	~RenderComponent();
};
