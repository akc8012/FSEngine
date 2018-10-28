#include "../Header/FSDebug.h"
#include <windows.h>

void FSDebug::Print(int message, const string& label)
{
	Print(std::to_string(message), label);
}

void FSDebug::Print(float message, const string& label)
{
	Print(std::to_string(message), label);
}

void FSDebug::Print(const mat4& matrix, const string& label)
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

	Print(matrixString, label);
}

void FSDebug::Print(const vec4& message, const string& label)
{
	string vectorString = "(" + std::to_string(message.x) + ", " + std::to_string(message.y) + ", " + std::to_string(message.z) + ", " + std::to_string(message.w) + ")";
	Print(vectorString, label);
}

void FSDebug::Print(const vec3& message, const string& label)
{
	string vectorString = "(" + std::to_string(message.x) + ", " + std::to_string(message.y) + ", " + std::to_string(message.z) + ")";
	Print(vectorString, label);
}

void FSDebug::Print(const vec2& vector, const string& label)
{
	string vectorString = "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
	Print(vectorString, label);
}

void FSDebug::Print(const string& message, const string& label)
{
	string labelText = (label != "") ? (label + ": ") : ("");

	printf("%s\n", (labelText + message).c_str());
	OutputDebugString((labelText + message + "\n").c_str());
}
