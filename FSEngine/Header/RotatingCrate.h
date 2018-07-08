#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using std::vector;

class RotatingCrate : public GameObject
{
private:
	vector<Vertex> CreateVertexList() const;

public:
	RotatingCrate(FileSystem* fileSystem, Input* input);
	void Update(float deltaTime);
};
