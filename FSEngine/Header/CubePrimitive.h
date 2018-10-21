#pragma once
#include "GameObject.h"

class CubePrimitive : public GameObject
{
private:
	shared_ptr<Mesh> CreateMeshComponent() const;

public:
	void Start() override;
	void Update() override;

	string GetGameObjectType() const override;
};
