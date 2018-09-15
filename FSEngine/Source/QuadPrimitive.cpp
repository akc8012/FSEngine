#include "../Header/QuadPrimitive.h"

QuadPrimitive::QuadPrimitive(const shared_ptr<ShadingComponent>& shadingComponent)
{
	shared_ptr<MeshComponent> meshComponent = AddComponent(CreateMeshComponent());
	meshComponent->GetParameterCollection()->SetParameter(MeshComponent::DrawElements, false);
	meshComponent->GetParameterCollection()->SetParameter(MeshComponent::RenderBackfaces, true);

	AddComponent(make_shared<TransformComponent>());
	AddComponent(shadingComponent);
}

shared_ptr<MeshComponent> QuadPrimitive::CreateMeshComponent() const
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
	return make_shared<MeshComponent>(rawVertices, Stride, indices);
}