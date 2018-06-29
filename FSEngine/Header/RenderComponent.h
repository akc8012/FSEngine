#pragma once
#include "Component.h"
#include "Texture.h"

#include <vector>

class RenderComponent : public Component
{
private:
	Texture* texture = nullptr;
	Uint32 vertexArrayId = NULL;

	std::vector<float> vertices;
	std::vector<Uint32> indices;
	Uint32 triangleCount;

	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride;
		int offset;
	};

	void CreateVertexArray(Uint32 stride);
	void SendVertices(Uint32 vertexBufferId, Uint32 stride);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute(Uint32 stride);
	void SendTextureAttribute(Uint32 stride);
	void SendVertexAttribute(const VertexAttribute& attribute);

public:
	RenderComponent(Texture* texture, std::vector<float> vertices, std::vector<Uint32> indices, Uint32 stride);
	~RenderComponent();

	void BindTextures();
	void BindVertexArray();

	Uint32 GetTriangleCount() const;
};
