#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
using namespace std;

class TransformComponent : public Component
{
private:
	mat4 transform = mat4(1.0f);
	// to-do: static constants for identity mat, up vec, etc
public:
	static string GetFormattedMatrixString(mat4 matrix);

	mat4 GetMatrix() const;
	vec3 GetPosition() const;
	//to-do: other getters

	void Scale(vec3 scaleVector);
	void Rotate(float angle, vec3 axis);
	void Translate(vec3 translation);

	void SetPosition(vec3 position);
	void SetRotation(float angle, vec3 axis);

	void LookAt(vec3 position, vec3 forwardVector, vec3 upVector);
};
