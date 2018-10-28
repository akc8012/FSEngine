#include "../Header/FSDebug.h"
#include <windows.h>

#pragma region Print
void FSDebug::Print(int message, const string& label)
{
	Print(to_string(message), label);
}

void FSDebug::Print(float message, const string& label)
{
	Print(to_string(message), label);
}

void FSDebug::Print(const mat4& message, const string& label)
{
	string matrixString = GetMatrixString(message);
	Print(matrixString, label);
}

void FSDebug::Print(const vec4& message, const string& label)
{
	string vectorString = GetVectorString(message);
	Print(vectorString, label);
}

void FSDebug::Print(const vec3& message, const string& label)
{
	string vectorString = GetVectorString(message);
	Print(vectorString, label);
}

void FSDebug::Print(const vec2& message, const string& label)
{
	string vectorString = GetVectorString(message);
	Print(vectorString, label);
}

void FSDebug::Print(const string& message, const string& label)
{
	string labelText = (label != "") ? (label + ": ") : ("");

	printf("%s\n", (labelText + message).c_str());
	OutputDebugString((labelText + message + "\n").c_str());
}
#pragma endregion

#pragma region Formatted Strings
string FSDebug::GetMatrixString(const mat4& matrix)
{
	string matrixString = "";

	const int ColumnAmount = 4, RowAmount = ColumnAmount;
	for (int col = 0; col < ColumnAmount; col++)
	{
		for (int row = 0; row < RowAmount; row++)
		{
			string comma = (row != RowAmount - 1) ? ", " : "";
			matrixString += to_string(matrix[col][row]) + comma;
		}

		matrixString += "\n";
	}

	return matrixString;
}

string FSDebug::GetVectorString(const vec4& vector)
{
	return "(" + to_string(vector.x) + ", " + to_string(vector.y) + ", " + to_string(vector.z) + ", " + to_string(vector.w) + ")";
}

string FSDebug::GetVectorString(const vec3& vector)
{
	return "(" + to_string(vector.x) + ", " + to_string(vector.y) + ", " + to_string(vector.z) + ")";
}

string FSDebug::GetVectorString(const vec2& vector)
{
	return "(" + to_string(vector.x) + ", " + to_string(vector.y) + ")";
}
#pragma endregion
