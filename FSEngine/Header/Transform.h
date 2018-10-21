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

class Transform : public Component
{
private:
	mat4 matrix = FSMath::IdentityMatrix;
	vec3 position = FSMath::Zero;
	vec3 scale = FSMath::One;
	quat orientation = FSMath::IdentityQuaternion;

	void CalculateMatrix();

public:
	static const Types::ComponentType ComponentTypeId = Types::Transform;
	Types::ComponentType GetComponentTypeId() const override;

	void Translate(const vec3& position);
	void SetPosition(float x, float y, float z);
	void SetPosition(const vec2& position);
	void SetPosition(const vec3& position);
	const vec3& GetPosition() const;

	void Scale(const vec2& scale);
	void Scale(const vec3& scale);
	void SetScale(float x, float y, float z);
	void SetScale(const vec2& scale);
	void SetScale(const vec3& scale);
	const vec3& GetScale() const;

	void SetOrientation(float eulerX, float eulerY, float eulerZ);
	void SetOrientation(const vec3& eulerAngles);
	void SetOrientation(const quat& orientation);
	void SetOrientation(float angle, const vec3& axis);
	vec3 GetForward() const;
	vec3 GetUp() const;
	vec3 GetRight() const;
	const quat& GetOrientation() const;
	vec3 GetEulerAngles() const;

	void SetMatrix(const mat4& matrix);
	mat3 CalculateNormalMatrix() const;
	const mat4& GetMatrix() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
