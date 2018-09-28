#include "../Header/Transform.h"

const mat4& Transform::GetMatrix() const
{
	return transform;
}

void Transform::SetMatrix(const mat4& matrix)
{
	transform = matrix;
}

mat3 Transform::CalculateNormalMatrix() const
{
	return mat3(transpose(inverse(transform)));
}

vec3 Transform::GetScale() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.scale;
}

quat Transform::GetOrientation() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.orientation;
}

vec3 Transform::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(GetOrientation()));
}

vec3 Transform::GetPosition() const
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return matrixValues.translation;
}

vec3 Transform::GetForward() const
{
	return GetOrientation() * FSMath::Forward;
}

vec3 Transform::GetUp() const
{
	return GetOrientation() * FSMath::Up;
}

vec3 Transform::GetRight() const
{
	return GetOrientation() * FSMath::Right;
}

Transform::MatrixValues Transform::DecomposeTransformMatrix() const
{
	MatrixValues matrixValues;
	decompose(transform, matrixValues.scale, matrixValues.orientation, matrixValues.translation, matrixValues.skew, matrixValues.perspective);
	return matrixValues;
}

const mat4& Transform::Scale(const vec2& scaleVector)
{
	return Scale(vec3(scaleVector, 1));
}

const mat4& Transform::Scale(float scaleFactor)
{
	return Scale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

const mat4& Transform::Scale(const vec3& scaleVector)
{
	transform = scale(transform, scaleVector);
	return transform;
}

const mat4& Transform::Translate(const vec2& translation)
{
	return Translate(vec3(translation, 0));
}

const mat4& Transform::Translate(const vec3& translation)
{
	vec3 currentPosition = DecomposeTransformMatrix().translation;
	transform = SetPosition(currentPosition + translation);
	return transform;
}

const mat4& Transform::SetScale(const vec2& scaleVector)
{
	return SetScale(vec3(scaleVector, 1));
}

const mat4& Transform::SetScale(float scaleFactor)
{
	return SetScale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

const mat4& Transform::SetScale(float x, float y, float z)
{
	return SetScale(vec3(x, y, z));
}

const mat4& Transform::SetScale(const vec3& scaleVector)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * toMat4(matrixValues.orientation) * scale(FSMath::IdentityMatrix, scaleVector);
	return transform;
}

const mat4& Transform::SetOrientation(const quat& orientation)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * glm::toMat4(orientation) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

const mat4& Transform::SetOrientation(const vec3& eulerAngles)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * glm::orientate4(glm::radians(eulerAngles)) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

const mat4& Transform::SetOrientation(float angle, const vec3& axis)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, matrixValues.translation) * rotate(FSMath::IdentityMatrix, angle, axis) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}

const mat4& Transform::SetPosition(const vec2& position)
{
	return SetPosition(vec3(position, 0));
}

const mat4& Transform::SetPosition(float x, float y, float z)
{
	return SetPosition(vec3(x, y, z));
}

const mat4& Transform::SetPosition(const vec3& position)
{
	MatrixValues matrixValues = DecomposeTransformMatrix();
	transform = translate(FSMath::IdentityMatrix, position) * toMat4(matrixValues.orientation) * scale(FSMath::IdentityMatrix, matrixValues.scale);
	return transform;
}
