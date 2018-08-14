#pragma once
#include "Component.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\matrix_decompose.hpp>
#include <glm\gtx\quaternion.hpp>
using namespace glm;

#include <string>
using std::string;

class TransformComponent : public Component
{
private:
	const mat4 identityMatrix = mat4(1);
	struct MatrixValues
	{
		vec3 scale;
		quat rotation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;
	};

	mat4 transform = mat4(1.0f);

	MatrixValues DecomposeTransformMatrix() const;

public:
	static const ComponentType ComponentTypeId = Transform;

	static string GetFormattedMatrixString(const mat4& matrix);
	static string GetFormattedVectorString(const vec3& vector);
	static string GetFormattedVectorString(const vec2& vector);

	mat4 GetMatrix() const;
	mat3 CalculateNormalMatrix() const;

	vec3 GetScale() const;
	quat GetRotation() const;
	vec3 GetEulerAngles() const;
	vec3 GetPosition() const;

	void SetMatrix(const mat4& matrix);
	mat4 Scale(const vec2& scaleVector);
	mat4 Scale(float scaleFactor);
	mat4 Scale(const vec3& scaleVector);
	mat4 Translate(const vec2& translation);
	mat4 Translate(const vec3& translation);

	mat4 SetScale(const vec2& scaleVector);
	mat4 SetScale(float scaleFactor);
	mat4 SetScale(const vec3& scaleVector);
	mat4 SetRotation(float angle, const vec3& axis);
	mat4 SetPosition(const vec2& position);
	mat4 SetPosition(const vec3& position);

	void LookAt(const vec3& position, const vec3& forwardVector, const vec3& upVector);
};
