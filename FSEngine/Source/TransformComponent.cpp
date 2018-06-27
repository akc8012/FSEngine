#include "../Header/TransformComponent.h"

string TransformComponent::GetFormattedMatrixString(mat4 matrix)
{
	string matrixString = "";

	const int ColumnAmount = 4, RowAmount = ColumnAmount;
	for (int col = 0; col < ColumnAmount; col++)
	{
		for (int row = 0; row < RowAmount; row++)
		{
			string comma = (row != RowAmount-1) ? ", " : "";
			matrixString += to_string(matrix[col][row]) + comma;
		}

		matrixString += "\n";
	}

	return matrixString;
}

mat4 TransformComponent::GetMatrix() const
{
	return transform;
}

vec3 TransformComponent::GetPosition() const
{
	const int PositionColumn = 3;
	return transform[PositionColumn];
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

void TransformComponent::SetRotation(float angle, vec3 axis)
{
	mat4 identity = mat4(1.0f);
	transform = rotate(identity, angle, axis);
}

void TransformComponent::SetPosition(vec3 position)
{
	mat4 identity = mat4(1.0f);
	transform = translate(identity, position);
}

void TransformComponent::LookAt(vec3 position, vec3 forwardVector, vec3 upVector)
{
	transform = lookAt(position, position + forwardVector, upVector);
}
