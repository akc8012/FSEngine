#pragma once
#include "GameObject.h"
#include "Camera.h"

class CameraFacingQuad : public GameObject
{
	Camera* camera = nullptr;
	Transform* transform = nullptr;

public:
	void Start() override;
	void SceneLoaded() override;
	void Update() override;

	string GetGameObjectType() const override;
};
