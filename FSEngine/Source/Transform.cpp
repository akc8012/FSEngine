#include "../Header/Transform.h"

#pragma region Position
void Transform::SetPosition(float x, float y, float z)
{
	SetPosition(vec3(x, y, z));
}

void Transform::SetPosition(const vec2& position)
{
	SetPosition(vec3(position.x, position.y, 0));
}

void Transform::SetPosition(const vec3& position)
{
	this->position = position;
	CalculateMatrix();
}

const vec3& Transform::GetPosition() const
{
	return position;
}
#pragma endregion

#pragma region Scale
void Transform::SetScale(float x, float y, float z)
{
	SetScale(vec3(x, y, z));
}

void Transform::SetScale(const vec2& scale)
{
	SetScale(vec3(scale.x, scale.y, 1));
}

void Transform::SetScale(const vec3& scale)
{
	this->scale = scale;
	CalculateMatrix();
}

const vec3& Transform::GetScale() const
{
	return scale;
}
#pragma endregion

#pragma region Orientation
void Transform::SetOrientation(float eulerX, float eulerY, float eulerZ)
{
	SetOrientation(vec3(eulerX, eulerY, eulerZ));
}

void Transform::SetOrientation(const vec3& eulerAngles)
{
	this->orientation = glm::orientate4(glm::radians(eulerAngles));
	CalculateMatrix();
}

void Transform::SetOrientation(const quat& orientation)
{
	this->orientation = glm::toMat4(orientation);
	CalculateMatrix();
}

void Transform::SetOrientation(float angle, const vec3& axis)
{
	this->orientation = glm::angleAxis(glm::radians(angle), axis);
	CalculateMatrix();
}

const quat& Transform::GetOrientation() const
{
	return orientation;
}
#pragma endregion

#pragma region Matrix
void Transform::CalculateMatrix()
{
	matrix = glm::translate(FSMath::IdentityMatrix, position) * glm::toMat4(orientation) * glm::scale(FSMath::IdentityMatrix, scale);
}

void Transform::SetMatrix(const mat4& matrix)
{
	this->matrix = matrix;

	vec3 unusedSkew; vec4 unusedPerspective;
	glm::decompose(this->matrix, scale, orientation, position, unusedSkew, unusedPerspective);
}

const mat4& Transform::GetMatrix() const
{
	return matrix;
}
#pragma endregion

json Transform::GetJson() const
{
	return json();
}

void Transform::SetFromJson(const json& j)
{

}
