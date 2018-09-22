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
#include <glm\gtx\euler_angles.hpp>

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
	void SetMatrix(const mat4& matrix);
	mat3 CalculateNormalMatrix() const;

	vec3 GetScale() const;
	vec3 GetEulerAngles() const;
	quat GetOrientation() const;
	vec3 GetPosition() const;

	vec3 GetForward() const;
	vec3 GetUp() const;
	vec3 GetRight() const;

	const mat4& Scale(const vec2& scaleVector);
	const mat4& Scale(float scaleFactor);
	const mat4& Scale(const vec3& scaleVector);
	const mat4& Translate(const vec2& translation);
	const mat4& Translate(const vec3& translation);

	const mat4& SetScale(const vec2& scaleVector);
	const mat4& SetScale(float scaleFactor);
	const mat4& SetScale(float x, float y, float z);
	const mat4& SetScale(const vec3& scaleVector);
	const mat4& SetOrientation(float angle, const vec3& axis);
	const mat4& SetOrientation(const vec3& eulerAngles);
	const mat4& SetPosition(const vec2& position);
	const mat4& SetPosition(float x, float y, float z);
	const mat4& SetPosition(const vec3& position);
};
