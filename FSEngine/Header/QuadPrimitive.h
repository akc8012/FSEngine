#pragma once
#include "GameObject.h"

class QuadPrimitive : public GameObject
{
public:
	void Start() override;

	string GetGameObjectType() const override;
};
