#include "../Header/TransformComponent.h"

const mat4& TransformComponent::GetMatrix() const
{
	return transform;
}

void TransformComponent::SetMatrix(const mat4& matrix)
{
	transform = matrix;
}

mat3 TransformComponent::CalculateNormalMatrix() const
{
	return mat3(transpose(inverse(transform)));
}

vec3 TransformComponent::GetScale() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.scale;
}

quat TransformComponent::GetOrientation() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.orientation;
}

vec3 TransformComponent::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(GetOrientation()));
}

vec3 TransformComponent::GetPosition() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.translation;
}

vec3 TransformComponent::GetForward() const
{
	return GetOrientation() * FSMath::Forward;
}

vec3 TransformComponent::GetUp() const
{
	return GetOrientation() * FSMath::Up;
}

vec3 TransformComponent::GetRight() const
{
	return GetOrientation() * FSMath::Right;
}

TransformComponent::MatrixValues TransformComponent::DecomposeTransformMatrix() const
{
	MatrixValues matrixValues;
	decompose(transform, matrixValues.scale, matrixValues.orientation, matrixValues.translation, matrixValues.skew, matrixValues.perspective);
	return matrixValues;
}

const mat4& TransformComponent::Scale(const vec2& scaleVector)
{
	return Scale(vec3(scaleVector, 1));
}

const mat4& TransformComponent::Scale(float scaleFactor)
{
	return Scale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

const mat4& TransformComponent::Scale(const vec3& scaleVector)
{
	transform = scale(transform, scaleVector);
	return transform;
}

const mat4& TransformComponent::Translate(const vec2& translation)
{
	return Translate(vec3(translation, 0));
}

const mat4& TransformComponent::Translate(const vec3& translation)
{
	vec3 currentPosition = DecomposeTransformMatrix().translation;
	transform = SetPosition(currentPosition + translation);
	return transform;
}

const mat4& TransformComponent::SetScale(const vec2& scaleVector)
{
	return SetScale(vec3(scaleVector, 1));
}

const mat4& TransformComponent::SetScale(float scaleFactor)
{
	return SetScale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

const mat4& TransformComponent::SetScale(float x, float y, float z)
{
	return SetScale(vec3(x, y, z));
}

const mat4& TransformComponent::SetScale(const vec3& scaleVector)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * toMat4(matrixValues.orientation) * scale(FSMath::IdentityMatrix, scaleVector);
	return transform;
}

const mat4& TransformComponent::SetOrientation(float angle, const vec3& axis)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * rotate(FSMath::IdentityMatrix, angle, axis) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

const mat4& TransformComponent::SetOrientation(const vec3& eulerAngles)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * glm::orientate4(glm::radians(eulerAngles)) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

const mat4& TransformComponent::SetPosition(const vec2& position)
{
	return SetPosition(vec3(position, 0));
}

const mat4& TransformComponent::SetPosition(float x, float y, float z)
{
	return SetPosition(vec3(x, y, z));
}

const mat4& TransformComponent::SetPosition(const vec3& position)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, position) * toMat4(matrixValues.orientation) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}
