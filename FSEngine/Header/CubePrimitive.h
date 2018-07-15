#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using std::vector;

class CubePrimitive : public GameObject
{
private:
	MeshComponent* CreateMeshComponent() const;

public:
	CubePrimitive(FileSystem* fileSystem, Input* input, Window* window);
	void Update(float deltaTime);
};
