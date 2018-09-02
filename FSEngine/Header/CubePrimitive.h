#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using std::vector;

class CubePrimitive : public GameObject
{
private:
	shared_ptr<MeshComponent> CreateMeshComponent() const;

public:
	CubePrimitive(const shared_ptr<ShadingComponent>& shadingComponent);

	void Update() override;
};
