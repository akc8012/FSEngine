#pragma once
#include "GameObject.h"

class QuadPrimitive : public GameObject
{
private:
	shared_ptr<Mesh> CreateMeshComponent() const;

public:
	QuadPrimitive(const shared_ptr<ShadingComponent>& shadingComponent);
};
