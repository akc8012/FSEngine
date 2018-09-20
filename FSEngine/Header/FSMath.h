#pragma once
#include <glm\glm.hpp>
using glm::vec3;
using glm::mat4;

namespace FSMath
{
	const mat4 IdentityMatrix = mat4(1);
	const vec3 Forward = vec3(0, 0, -1);
	const vec3 Up = vec3(0, 1, 0);
	const vec3 Right = vec3(1, 0, 0);
	const vec3 Zero = vec3(0, 0, 0);
	const vec3 One = vec3(1, 1, 1);

	vec3 EulerAngleToDirectionVector(const vec3& angle);
	vec3 NanToZero(vec3 vector);
}

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
