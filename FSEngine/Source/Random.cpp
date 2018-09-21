#include "../Header/Random.h"

int Random::GetRandomRange(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float Random::GetRandomRange(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

vec3 Random::GetRandomUniformVector(float min, float max)
{
	return vec3(GetRandomRange(min, max), GetRandomRange(min, max), GetRandomRange(min, max));
}
