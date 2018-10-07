#include "../Header/QuadPrimitive.h"

void QuadPrimitive::Start()
{
	Mesh* meshComponent = components->mesh->Add(GetName(), CreateMeshComponent());
	meshComponent->GetParameterCollection()->SetParameter(Mesh::DrawElements, false);
	meshComponent->GetParameterCollection()->SetParameter(Mesh::RenderBackfaces, true);

	components->transform->Add(GetName(), make_shared<Transform>());
}

shared_ptr<Mesh> QuadPrimitive::CreateMeshComponent() const
{
	vector<float> rawVertices =
	{
		// positions         // normals           // textureCoords
	   -0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	const int Stride = 8;
	return make_shared<Mesh>(rawVertices, Stride, indices);
}
