#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using namespace std;

class RotatingCrate : public GameObject
{
private:


public:
	RotatingCrate(Texture* texture, vec3 position);

	void Update(Uint32 deltaTime);
};
