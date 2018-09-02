#pragma once
#include "Component.h"
#include "Vertex.h"
#include "ParameterCollection.h"

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
	enum Parameters
	{
		RenderBackfaces,
		DrawElements,

		ParametersLength
	};

private:
	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride = sizeof(Vertex);
		size_t offset;
	};

	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	vector<Vertex> vertices;
	vector<Uint32> indices;
	vector<string> associatedTextureNames;

	Uint32 vertexArrayId = NULL;

	void Initialize();
	vector<Vertex> ConvertRawVertices(const vector<float>& rawVertices, int stride) const;
	void CreateVertexArray();

	void SendVertices(Uint32 vertexBufferId);
	void SendIndices(Uint32 elementBufferId);

	void SendPositionAttribute();
	void SendNormalAttribute();
	void SendTextureAttribute();

	void SendVertexAttribute(const VertexAttribute& attribute);

	void DrawTriangleElements();
	void DrawTriangleArrays();

public:
	static const ComponentType ComponentTypeId = Mesh;

	MeshComponent(const vector<Vertex>& vertices, const vector<Uint32>& indices);
	MeshComponent(const vector<float>& rawVertices, int stride, const vector<Uint32>& indices);
	~MeshComponent();

	void BindVertexArray();
	void DrawMesh();

	int GetIndiceCount() const;
	int GetVerticeCount() const;

	void AddAssociatedTextureName(const string& textureName);
	void AddAssociatedTextureIndices(const vector<string>& textureNames);
	const vector<string>& GetAssociatedTextureNames() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
