#include "../Header/TransformComponent.h"

string TransformComponent::GetFormattedMatrixString(const mat4& matrix)
{
	string matrixString = "";

	const int ColumnAmount = 4, RowAmount = ColumnAmount;
	for (int col = 0; col < ColumnAmount; col++)
	{
		for (int row = 0; row < RowAmount; row++)
		{
			string comma = (row != RowAmount-1) ? ", " : "";
			matrixString += std::to_string(matrix[col][row]) + comma;
		}

		matrixString += "\n";
	}

	return matrixString;
}

string TransformComponent::GetFormattedVectorString(const vec3& vector)
{
	return "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ", " + std::to_string(vector.z) + ")";
}

string TransformComponent::GetFormattedVectorString(const vec2& vector)
{
	return "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
}

mat4 TransformComponent::GetMatrix() const
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
	MatrixValues matrixValues = DecomposeTransformMatrix();
	return eulerAngles(matrixValues.rotation);
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

void TransformComponent::Scale(const vec2& scaleVector)
{
	Scale(vec3(scaleVector, 1));
}

void TransformComponent::Scale(const vec3& scaleVector)
{
	transform = scale(transform, scaleVector);
}

void TransformComponent::Scale(float scaleFactor)
{
	transform = scale(transform, vec3(scaleFactor, scaleFactor, scaleFactor));
}

void TransformComponent::Rotate(float angle, const vec3& axis)
{
	transform = rotate(transform, angle, axis);
}

void TransformComponent::Translate(const vec2& translation)
{
	Translate(vec3(translation, 0));
}

void TransformComponent::Translate(const vec3& translation)
{
	transform = translate(transform, translation);
}

void TransformComponent::SetScale(const vec2& scaleVector)
{
	SetScale(vec3(scaleVector, 1));
}

void TransformComponent::SetScale(float scaleFactor)
{
	SetScale(vec3(scaleFactor, scaleFactor, scaleFactor));
}

void TransformComponent::SetScale(const vec3& scaleVector)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, matrixValues.translation) * toMat4(matrixValues.rotation) * scale(identity, scaleVector);
}

void TransformComponent::SetRotation(float angle, const vec3& axis)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, matrixValues.translation) * rotate(identity, angle, axis) * scale(identity, matrixValues.scale);
}

void TransformComponent::SetPosition(const vec2& position)
{
	SetPosition(vec3(position, 0));
}

void TransformComponent::SetPosition(const vec3& position)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, position) * toMat4(matrixValues.rotation) * scale(identity, matrixValues.scale);
}

void TransformComponent::LookAt(const vec3& position, const vec3& forwardVector, const vec3& upVector)
{
	transform = lookAt(position, position + forwardVector, upVector);
}
