#pragma once
#include "Component.h"
#include "FSMath.h"
#include "ParameterCollection.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <vector>
using std::vector;

class Mesh : public Component
{
public:
	enum Parameters { RenderBackfaces, DrawElements, ParametersLength };

protected:
	vector<vertex> ConvertRawVertices(const vector<float>& rawVertices, int stride) const;
	void CreateVertexArray(const vector<vertex>& vertices, const vector<Uint32>& indices);

private:
	struct VertexAttribute
	{
		int location;
		int size;
		bool normalize = false;
		int stride = sizeof(vertex);
		size_t offset;
	};

	int verticeCount;
	int indiceCount;
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;
	string shadingName;
	Uint32 vertexArrayId = NULL;

	void SendVertices(Uint32 vertexBufferId, const vector<vertex>& vertices);
	void SendIndices(Uint32 elementBufferId, const vector<Uint32>& indices);

	void SendPositionAttribute();
	void SendNormalAttribute();
	void SendTextureAttribute();

	void SendVertexAttribute(const VertexAttribute& attribute);

public:
	static const Types::ComponentType ComponentTypeId = Types::Mesh;
	virtual Types::ComponentType GetComponentTypeId() const override;

	Mesh(const vector<vertex>& vertices, const vector<Uint32>& indices);
	Mesh(const vector<float>& rawVertices, int stride, const vector<Uint32>& indices);
	Mesh();
	~Mesh();

	int GetVerticeCount() const;
	int GetIndiceCount() const;

	void BindVertexArray();

	void SetShadingName(const string& shadingName);
	const string& GetShadingName() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
