#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;

#include <string>

class TransformComponent : public Component
{
private:
	mat4 transform = mat4(1.0f);

	struct MatrixValues
	{
		vec3 scale;
		quat rotation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;
	};

public:
	static std::string GetFormattedMatrixString(const mat4& matrix);

	mat4 GetMatrix() const;

	vec3 GetScale() const;
	quat GetRotation() const;
	vec3 GetEulerAngles() const;
	vec3 GetPosition() const;
	MatrixValues DecomposeTransformMatrix() const;

	void Scale(const vec3& scaleVector);
	void Rotate(float angle, const vec3& axis);
	void Translate(const vec3& translation);

	void SetScale(const vec3& scaleVector);
	void SetRotation(float angle, const vec3& axis);
	void SetPosition(const vec3& position);

	void LookAt(const vec3& position, const vec3& forwardVector, const vec3& upVector);
};
