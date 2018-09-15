#pragma once
#include "GameObject.h"

class QuadPrimitive : public GameObject
{
private:
	shared_ptr<MeshComponent> CreateMeshComponent() const;

public:
	QuadPrimitive(const shared_ptr<ShadingComponent>& shadingComponent);
};
