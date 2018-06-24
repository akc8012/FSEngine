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

public:
	static string GetFormattedMatrixString(mat4 matrix);

	mat4 GetMatrix();
	vec3 GetPosition();
	//to-do: other getters

	void Scale(vec3 scaleVector);
	void Rotate(float angle, vec3 axis);
	void Translate(vec3 translation);
};
