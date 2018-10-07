#pragma once
#include "GameObject.h"

class QuadPrimitive : public GameObject
{
private:
	shared_ptr<Mesh> CreateMeshComponent() const;

public:
	void Start() override;
};
