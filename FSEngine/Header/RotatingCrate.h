#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>

class RotatingCrate : public GameObject
{
private:


public:
	RotatingCrate(FileSystem* fileSystem, TextureComponent* textureComponent);

	void Update(Uint32 deltaTime);
};
