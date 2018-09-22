#pragma once
#include "Component.h"
#include "FSMath.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using glm::mat4;
using glm::mat3;
using glm::quat;
using glm::vec4;
using glm::vec3;
using glm::vec2;

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\matrix_decompose.hpp>
#include <glm\gtx\quaternion.hpp>

#include <string>
using std::string;

class TransformComponent : public Component
{
private:
	struct MatrixValues
	{
		vec3 scale;
		quat orientation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;
	};

	mat4 transform = FSMath::IdentityMatrix;

	MatrixValues DecomposeTransformMatrix() const;

public:
	static const ComponentType ComponentTypeId = Transform;

	const mat4& GetMatrix() const;
	mat3 CalculateNormalMatrix() const;

	vec3 GetScale() const;
	vec3 GetEulerAngles() const;
	quat GetOrientation() const;
	vec3 GetPosition() const;

	void SetMatrix(const mat4& matrix);
	mat4 Scale(const vec2& scaleVector);
	mat4 Scale(float scaleFactor);
	mat4 Scale(const vec3& scaleVector);
	mat4 Translate(const vec2& translation);
	mat4 Translate(const vec3& translation);

	mat4 SetScale(const vec2& scaleVector);
	mat4 SetScale(float scaleFactor);
	mat4 SetScale(float x, float y, float z);
	mat4 SetScale(const vec3& scaleVector);
	mat4 SetOrientation(float angle, const vec3& axis);
	mat4 SetPosition(const vec2& position);
	mat4 SetPosition(float x, float y, float z);
	mat4 SetPosition(const vec3& position);
};
