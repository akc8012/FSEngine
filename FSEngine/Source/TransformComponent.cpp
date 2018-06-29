#include "../Header/TransformComponent.h"

std::string TransformComponent::GetFormattedMatrixString(mat4 matrix)
{
	using std::string;

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

mat4 TransformComponent::GetMatrix() const
{
	return transform;
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

void TransformComponent::Scale(vec3 scaleVector)
{
	transform = scale(transform, scaleVector);
}

void TransformComponent::Rotate(float angle, vec3 axis)
{
	transform = rotate(transform, angle, axis);
}

void TransformComponent::Translate(vec3 translation)
{
	transform = translate(transform, translation);
}

void TransformComponent::SetScale(vec3 scaleVector)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, matrixValues.translation) * toMat4(matrixValues.rotation) * scale(identity, scaleVector);
}

void TransformComponent::SetRotation(float angle, vec3 axis)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, matrixValues.translation) * rotate(identity, angle, axis) * scale(identity, matrixValues.scale);
}

void TransformComponent::SetPosition(vec3 position)
{
	mat4 identity = mat4(1.0f);
	MatrixValues matrixValues = DecomposeTransformMatrix();

	transform = translate(identity, position) * toMat4(matrixValues.rotation) * scale(identity, matrixValues.scale);
}

void TransformComponent::LookAt(vec3 position, vec3 forwardVector, vec3 upVector)
{
	transform = lookAt(position, position + forwardVector, upVector);
}
