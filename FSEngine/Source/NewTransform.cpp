#include "../Header/NewTransform.h"

#pragma region Position
void NewTransform::SetPosition(float x, float y, float z)
{
	SetPosition(vec3(x, y, z));
}

void NewTransform::SetPosition(const vec2& position)
{
	SetPosition(vec3(position.x, position.y, 0));
}

void NewTransform::SetPosition(const vec3& position)
{
	this->position = position;
	CalculateMatrix();
}

const vec3& NewTransform::GetPosition() const
{
	return position;
}
#pragma endregion

#pragma region Scale
void NewTransform::SetScale(float x, float y, float z)
{
	SetScale(vec3(x, y, z));
}

void NewTransform::SetScale(const vec2& scale)
{
	SetScale(vec3(scale.x, scale.y, 1));
}

void NewTransform::SetScale(const vec3& scale)
{
	this->scale = scale;
	CalculateMatrix();
}

const vec3& NewTransform::GetScale() const
{
	return scale;
}
#pragma endregion

#pragma region Orientation
void NewTransform::SetOrientation(float eulerX, float eulerY, float eulerZ)
{
	SetOrientation(vec3(eulerX, eulerY, eulerZ));
}

void NewTransform::SetOrientation(const vec3& eulerAngles)
{
	this->orientation = glm::orientate4(glm::radians(eulerAngles));
	CalculateMatrix();
}

void NewTransform::SetOrientation(const quat& orientation)
{
	this->orientation = glm::toMat4(orientation);
	CalculateMatrix();
}

void NewTransform::SetOrientation(float angle, const vec3& axis)
{
	this->orientation = glm::angleAxis(glm::radians(angle), axis);
	CalculateMatrix();
}

const quat& NewTransform::GetOrientation() const
{
	return orientation;
}
#pragma endregion

#pragma region Matrix
void NewTransform::CalculateMatrix()
{
	matrix = glm::translate(FSMath::IdentityMatrix, position) * glm::toMat4(orientation) * glm::scale(FSMath::IdentityMatrix, scale);
}

void NewTransform::SetMatrix(const mat4& matrix)
{
	this->matrix = matrix;

	vec3 unusedSkew; vec4 unusedPerspective;
	glm::decompose(this->matrix, scale, orientation, position, unusedSkew, unusedPerspective);
}

const mat4& NewTransform::GetMatrix() const
{
	return matrix;
}
#pragma endregion

json NewTransform::GetJson() const
{
	return json();
}

void NewTransform::SetFromJson(const json& j)
{

}
