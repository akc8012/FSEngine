#include "../Header/NewTransform.h"

void NewTransform::SetPosition(const vec3& position)
{
	this->position = position;
}

const vec3& NewTransform::GetPosition() const
{
	return position;
}

void NewTransform::SetScale(const vec3& scale)
{
	this->scale = scale;
}

const vec3& NewTransform::GetScale() const
{
	return scale;
}

mat4 NewTransform::GetMatrix() const
{
	return glm::translate(FSMath::IdentityMatrix, position) * glm::toMat4(orientation) * glm::scale(FSMath::IdentityMatrix, scale);
}

json NewTransform::GetJson() const
{
	return json();
}

void NewTransform::SetFromJson(const json& j)
{

}
