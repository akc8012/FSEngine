#pragma once
#include "GameObject.h"
#include "ClickLabel.h"

class ClickLabelManager : public GameObject
{
public:
	void Start() override;
	void SceneLoaded() override;

	string GetGameObjectType() const override;
};
