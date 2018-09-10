#include "../Header/FSDebug.h"

void FSDebug::Print(int message)
{
	Print(std::to_string(message));
}

void FSDebug::Print(float message)
{
	Print(std::to_string(message));
}

void FSDebug::Print(const string& message)
{
	printf("%s\n", message.c_str());
}
