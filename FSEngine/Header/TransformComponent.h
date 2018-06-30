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
	struct MatrixValues
	{
		vec3 scale;
		quat rotation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;
	};

	mat4 transform = mat4(1.0f);

public:
	static std::string GetFormattedMatrixString(mat4 matrix);

	mat4 GetMatrix() const;

	vec3 GetScale() const;
	quat GetRotation() const;
	vec3 GetEulerAngles() const;
	vec3 GetPosition() const;
	MatrixValues DecomposeTransformMatrix() const;

	void Scale(vec3 scaleVector);
	void Rotate(float angle, vec3 axis);
	void Translate(vec3 translation);

	void SetScale(vec3 scaleVector);
	void SetRotation(float angle, vec3 axis);
	void SetPosition(vec3 position);

	void LookAt(vec3 position, vec3 forwardVector, vec3 upVector);
};
