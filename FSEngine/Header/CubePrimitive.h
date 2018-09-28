#pragma once
#include "GameObject.h"

class CubePrimitive : public GameObject
{
private:
	shared_ptr<Mesh> CreateMeshComponent() const;

public:
	CubePrimitive(const shared_ptr<ShadingComponent>& shadingComponent);

	void Update() override;
};
