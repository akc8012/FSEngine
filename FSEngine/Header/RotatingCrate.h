#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>

class RotatingCrate : public GameObject
{
private:


public:
	RotatingCrate(FileSystem* fileSystem);
	void Update(Uint32 deltaTime);
};
