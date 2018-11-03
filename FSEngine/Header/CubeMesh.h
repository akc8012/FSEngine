#pragma once
#include "Mesh.h"

class CubeMesh : public Mesh
{
public:
	static const Types::ComponentType ComponentTypeId = Types::CubeMesh;
	Types::ComponentType GetComponentTypeId() const override;

	CubeMesh();
};
