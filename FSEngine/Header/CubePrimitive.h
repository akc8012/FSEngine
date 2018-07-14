#pragma once
#include "GameObject.h"
#include "Timer.h"

#include <vector>
using std::vector;

class CubePrimitive : public GameObject
{
private:
	vector<Vertex> CreateVertexList() const;

public:
	CubePrimitive(FileSystem* fileSystem, Input* input, Window* window);
	void Update(float deltaTime);
};
