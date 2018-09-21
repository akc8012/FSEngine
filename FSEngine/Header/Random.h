#pragma once
#include <glm\glm.hpp>
using glm::vec3;

#include <random>

class Random
{
private:
	std::default_random_engine generator;

public:
	int GetRandomRange(int min, int max);
	float GetRandomRange(float min, float max);
	vec3 GetRandomUniformVector(float min, float max);
};
