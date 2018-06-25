#pragma once
#include "Component.h"
#include "Texture.h"

#include <vector>
using namespace std;

class RenderComponent : public Component
{
private:
	Texture* texture = NULL;
	Uint32 vertexArrayId = 0;

	vector<float> vertices;
	vector<Uint32> indices;

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
	RenderComponent(vector<float> vertices, vector<Uint32> indices, const char* textureFilepath);
	~RenderComponent();

	void BindTextures();
	void BindVertexArray();
};
