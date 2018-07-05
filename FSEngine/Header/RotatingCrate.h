#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>

class RotatingCrate : public GameObject
{
private:


public:
	RotatingCrate(FileSystem* fileSystem, Input* input);
	void Update(float deltaTime);
};
