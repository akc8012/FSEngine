#pragma once
#include "Mesh.h"

class QuadMesh : public Mesh
{
public:
	static const Types::ComponentType ComponentTypeId = Types::QuadMesh;
	Types::ComponentType GetComponentTypeId() const override;

	QuadMesh();
};
