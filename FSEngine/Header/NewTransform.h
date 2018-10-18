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

class NewTransform : public Component
{
private:
	vec3 position;
	vec3 scale = FSMath::One;
	quat orientation;

public:
	static const Types::ComponentType ComponentTypeId = Types::NewTransform;

	void SetPosition(const vec3& position);
	const vec3& GetPosition() const;

	mat4 GetMatrix() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
