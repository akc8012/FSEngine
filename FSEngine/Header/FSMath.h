#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec2;
using glm::quat;
using glm::tquat;

namespace FSMath
{
	const mat4 IdentityMatrix = mat4(1);
	const quat IdentityQuaternion = quat(1, 0, 0, 0);
	const vec3 Forward = vec3(0, 0, -1);
	const vec3 Up = vec3(0, 1, 0);
	const vec3 Right = vec3(1, 0, 0);
	const vec3 Zero = vec3(0, 0, 0);
	const vec3 One = vec3(1, 1, 1);

	using dquat = tquat<double>;

	vec3 EulerAngleToDirectionVector(const vec3& angle);
	vec3 NanToZero(vec3 vector);

	// https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp
	quat RotationBetweenVectors(vec3 start, vec3 dest);
	quat LookAt(vec3 direction, vec3 desiredUp);
}

struct vertex
{
	vertex() { }

	vertex(const vec3& position, const vec3& normal, const vec2& textureCoord)
	 : position(position), normal(normal), textureCoord(textureCoord)
	{

	}

	vec3 position;
	vec3 normal;
	vec2 textureCoord;
};

struct ray
{
	ray() { }

	ray(const vec3& origin, const vec3& direction)
	 : origin(origin), direction(direction)
	{

	}

	vec3 origin;
	vec3 direction;
};

struct plane
{
	plane() { }

	plane(const vec3& origin, const vec3& normal)
	 : origin(origin), normal(normal)
	{

	}

	vec3 origin;
	vec3 normal;
};
