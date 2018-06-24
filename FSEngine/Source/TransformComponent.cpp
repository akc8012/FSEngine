#include "../Header/TransformComponent.h"

string TransformComponent::GetFormattedMatrixString(mat4 matrix)
{
	string matrixString = "";

	const int ColumnAmount = 4, RowAmount = ColumnAmount;
	for (int col = 0; col < ColumnAmount; col++)
	{
		for (int row = 0; row < RowAmount; row++)
		{
			bool addComma = row != RowAmount-1;
			matrixString += to_string(matrix[col][row]) + (addComma ? ", " : "");
		}

		matrixString += "\n";
	}

	return matrixString;
}

mat4 TransformComponent::GetMatrix()
{
	return transform;
}

vec3 TransformComponent::GetPosition()
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
