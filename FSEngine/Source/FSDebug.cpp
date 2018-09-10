#include "../Header/FSDebug.h"

void FSDebug::Print(int message)
{
	Print(std::to_string(message));
}

void FSDebug::Print(float message)
{
	Print(std::to_string(message));
}

void FSDebug::Print(const mat4& matrix)
{
	string matrixString = "";

	const int ColumnAmount = 4, RowAmount = ColumnAmount;
	for (int col = 0; col < ColumnAmount; col++)
	{
		for (int row = 0; row < RowAmount; row++)
		{
			string comma = (row != RowAmount - 1) ? ", " : "";
			matrixString += std::to_string(matrix[col][row]) + comma;
		}

		matrixString += "\n";
	}

	Print(matrixString);
}

void FSDebug::Print(const vec3& message)
{
	string vectorString = "(" + std::to_string(message.x) + ", " + std::to_string(message.y) + ", " + std::to_string(message.z) + ")";
	Print(vectorString);
}

void FSDebug::Print(const vec2& vector)
{
	string vectorString = "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
	Print(vectorString);
}

void FSDebug::Print(const string& message)
{
	printf("%s\n", message.c_str());
}
