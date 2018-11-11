#pragma once
#include "GameObject.h"

class ClickLabelManager : public GameObject
{
public:
	void Start() override;

	string GetGameObjectType() const override;
};
