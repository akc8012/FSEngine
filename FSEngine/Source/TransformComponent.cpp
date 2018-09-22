#include "../Header/TransformComponent.h"

const mat4& TransformComponent::GetMatrix() const
{
	return transform;
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

quat TransformComponent::GetRotation() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.rotation;
}

vec3 TransformComponent::GetEulerAngles() const
{
	return eulerAngles(GetRotation());
}

vec3 TransformComponent::GetPosition() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.translation;
}

TransformComponent::MatrixValues TransformComponent::DecomposeTransformMatrix() const
{
	MatrixValues matrixValues;
	decompose(transform, matrixValues.scale, matrixValues.rotation, matrixValues.translation, matrixValues.skew, matrixValues.perspective);
	return matrixValues;
}

void TransformComponent::SetMatrix(const mat4& matrix)
{
	transform = matrix;
}

mat4 TransformComponent::Scale(const vec2& scaleVector)
{
	return Scale(vec3(scaleVector, 1));
}

mat4 TransformComponent::Scale(float scaleFactor)
{
	return Scale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

mat4 TransformComponent::Scale(const vec3& scaleVector)
{
	transform = scale(transform, scaleVector);
	return transform;
}

mat4 TransformComponent::Translate(const vec2& translation)
{
	return Translate(vec3(translation, 0));
}

mat4 TransformComponent::Translate(const vec3& translation)
{
	vec3 currentPosition = DecomposeTransformMatrix().translation;
	transform = SetPosition(currentPosition + translation);
	return transform;
}

mat4 TransformComponent::SetScale(const vec2& scaleVector)
{
	return SetScale(vec3(scaleVector, 1));
}

mat4 TransformComponent::SetScale(float scaleFactor)
{
	return SetScale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

mat4 TransformComponent::SetScale(float x, float y, float z)
{
	return SetScale(vec3(x, y, z));
}

mat4 TransformComponent::SetScale(const vec3& scaleVector)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * toMat4(matrixValues.rotation) * scale(FSMath::IdentityMatrix, scaleVector);
	return transform;
}

mat4 TransformComponent::SetRotation(float angle, const vec3& axis)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * rotate(FSMath::IdentityMatrix, angle, axis) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

mat4 TransformComponent::SetRotation(const vec3& eulerAngles)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * glm::orientate4(glm::radians(eulerAngles)) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

mat4 TransformComponent::SetPosition(const vec2& position)
{
	return SetPosition(vec3(position, 0));
}

mat4 TransformComponent::SetPosition(float x, float y, float z)
{
	return SetPosition(vec3(x, y, z));
}

mat4 TransformComponent::SetPosition(const vec3& position)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, position) * toMat4(matrixValues.rotation) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}
