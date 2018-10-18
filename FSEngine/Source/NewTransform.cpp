#include "../Header/NewTransform.h"

void NewTransform::SetPosition(const vec3& position)
{
	this->position = position;
}

const vec3& NewTransform::GetPosition() const
{
	return position;
}

mat4 NewTransform::GetMatrix() const
{
	return glm::scale(FSMath::IdentityMatrix, scale) * glm::toMat4(orientation) * glm::translate(FSMath::IdentityMatrix, position);
}

json NewTransform::GetJson() const
{
	return json();
}

void NewTransform::SetFromJson(const json& j)
{

}
