#pragma once
#include "Model.h"
#include "Camera.h"

class PlayerShip : public Model
{
private:
	TransformComponent* transform = nullptr;
	Camera* camera = nullptr;

public:
	PlayerShip();

	void Start();
	void Update(float deltaTime);
};
