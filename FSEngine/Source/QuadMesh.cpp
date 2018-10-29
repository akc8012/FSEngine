#include "../Header/QuadMesh.h"

QuadMesh::QuadMesh()
{
	vector<float> rawVertices =
	{
		 // positions        // normals          // texture coords
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f
	};

	const int Stride = 8;
	vertices = ConvertRawVertices(rawVertices, Stride);

	indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Initialize();
}
