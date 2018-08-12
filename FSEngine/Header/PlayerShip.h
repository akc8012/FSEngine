#pragma once
#include "Model.h"

class PlayerShip : public Model
{
private:
	TransformComponent* transform = nullptr;

public:
	PlayerShip();

	void Start();
	void Update(float deltaTime);
};
