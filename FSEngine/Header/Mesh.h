#pragma once
#include "Component.h"
#include "Vertex.h"
#include "ParameterCollection.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <vector>
using std::vector;

class Mesh : public Component
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
	static const Types::ComponentType ComponentTypeId = Types::Mesh;

	Mesh();
	Mesh(const vector<Vertex>& vertices, const vector<Uint32>& indices);
	Mesh(const vector<float>& rawVertices, int stride, const vector<Uint32>& indices);
	~Mesh();

	void BindVertexArray();
	void DrawMesh();

	int GetIndiceCount() const;
	int GetVerticeCount() const;

	void AddAssociatedTextureName(const string& textureName);
	void AddAssociatedTextureIndices(const vector<string>& textureNames);
	const vector<string>& GetAssociatedTextureNames() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
