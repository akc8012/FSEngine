#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using namespace std;

class RotatingCrate : public GameObject
{
private:

public:
	RotatingCrate();
	~RotatingCrate();

	void Update(Uint32 deltaTime);
};
