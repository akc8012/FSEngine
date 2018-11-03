#pragma once
#include "GameObject.h"

class CameraFacingQuad : public GameObject
{
public:
	void Start() override;

	string GetGameObjectType() const override;
};
