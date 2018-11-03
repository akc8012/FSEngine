#pragma once
#include "GameObject.h"

class CubePrimitive : public GameObject
{
public:
	void Start() override;
	void Update() override;

	string GetGameObjectType() const override;
};
