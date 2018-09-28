#pragma once
#include "Model.h"
#include "Camera.h"

class PlayerShip : public Model
{
private:
	Transform* transform = nullptr;
	Camera* camera = nullptr;

	vec3 direction;

	void ResetValues();
	void ControlShip();
	void SetCamera();

	float GetFrameAdjustedSpeed() const;

public:
	PlayerShip();

	void Start() override;
	void Update() override;
};
