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
public:
	enum DrawingMode { Arrays, Elements };

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
	vector<string> associatedTextureNames;

	Uint32 vertexArrayId = NULL;
	bool renderBackfaces = false;
	DrawingMode drawingMode = Elements;

	vector<Vertex> ConvertRawVertices(const vector<float>& rawVertices, int stride) const;

	void CreateVertexArray();

	void SendVertices(Uint32 vertexBufferId);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute();
	void SendNormalAttribute();
	void SendTextureAttribute();

	void SendVertexAttribute(const VertexAttribute& attribute);

public:
	static const ComponentType ComponentTypeId = Mesh;

	MeshComponent(const vector<Vertex>& vertices, const vector<Uint32>& indices);
	MeshComponent(const vector<float>& rawVertices, int stride, const vector<Uint32>& indices);
	~MeshComponent();

	void BindVertexArray();

	int GetIndiceCount() const;
	int GetVerticeCount() const;

	void SetRenderBackfaces(bool renderBackfaces);
	bool RenderBackfaces() const;
	void SetDrawingMode(DrawingMode drawingMode);
	DrawingMode GetDrawingMode() const;

	void AddAssociatedTextureName(string textureName);
	void AddAssociatedTextureIndices(const vector<string>& textureNames);
	vector<string> GetAssociatedTextureNames() const;
};
