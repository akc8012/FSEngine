#pragma once
#include <glm\glm.hpp>
using glm::vec3;

struct ray
{
	ray(const vec3& origin, const vec3& direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	vec3 origin;
	vec3 direction;
};

struct plane
{
	plane(const vec3& origin, const vec3& normal)
	{
		this->origin = origin;
		this->normal = normal;
	}

	vec3 origin;
	vec3 normal;
};
