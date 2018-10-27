#include "../Header/Transform.h"

#pragma region Position
void Transform::Translate(const vec3& position)
{
	SetPosition(this->position + position);
}

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
void Transform::Scale(const vec2& scale)
{
	SetScale(this->scale * vec3(scale.x, scale.y, 1));
}

void Transform::Scale(const vec3& scale)
{
	SetScale(this->scale * scale);
}

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
	this->orientation = quat(glm::radians(eulerAngles));
	CalculateMatrix();
}

void Transform::SetOrientation(const dquat& orientation)
{
	this->orientation = orientation;
	CalculateMatrix();
}

void Transform::SetOrientation(float angle, const vec3& axis)
{
	this->orientation = glm::angleAxis(glm::radians(angle), axis);
	CalculateMatrix();
}

vec3 Transform::GetForward() const
{
	return GetOrientation() * tvec3<double>(FSMath::Forward);
}

vec3 Transform::GetUp() const
{
	return GetOrientation() * tvec3<double>(FSMath::Up);
}

vec3 Transform::GetRight() const
{
	return GetOrientation() * tvec3<double>(FSMath::Right);
}

const dquat& Transform::GetOrientation() const
{
	return orientation;
}

vec3 Transform::GetEulerAngles() const
{
	vec3 euler = glm::eulerAngles(orientation);
	return glm::degrees(euler);
}
#pragma endregion

#pragma region Matrix
void Transform::CalculateMatrix()
{
	matrix = glm::translate(FSMath::IdentityMatrix, position) * glm::toMat4(quat(orientation)) * glm::scale(FSMath::IdentityMatrix, scale);
}

void Transform::SetMatrix(const mat4& matrix)
{
	this->matrix = matrix;

	vec3 unusedSkew; vec4 unusedPerspective; quat floatOrientation;
	glm::decompose(this->matrix, scale, floatOrientation, position, unusedSkew, unusedPerspective);
	this->orientation = floatOrientation;
}

mat3 Transform::CalculateNormalMatrix() const
{
	return mat3(glm::transpose(glm::inverse(matrix)));
}

const mat4& Transform::GetMatrix() const
{
	return matrix;
}
#pragma endregion

json Transform::GetJson() const
{
	json j;
	j["type"] = Types::ComponentTypeString[ComponentTypeId];

	vec3 position = GetPosition();
	j["Position"] = { position.x, position.y, position.z };

	vec3 eulerAngles = GetEulerAngles();
	j["EulerAngles"] = { eulerAngles.x, eulerAngles.y, eulerAngles.z };

	vec3 scale = GetScale();
	j["Scale"] = { scale.x, scale.y, scale.z };

	return j;
}

void Transform::SetFromJson(const json& j)
{
	json position = j["Position"];
	SetPosition(position[0], position[1], position[2]);

	json eulerAngles = j["EulerAngles"];
	SetOrientation(eulerAngles[0], eulerAngles[1], eulerAngles[2]);

	json scale = j["Scale"];
	SetScale(scale[0], scale[1], scale[2]);
}

Types::ComponentType Transform::GetComponentTypeId() const
{
	return ComponentTypeId;
}
