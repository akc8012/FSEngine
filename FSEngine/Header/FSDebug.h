#pragma once

#include <string>
#include <typeinfo>
using std::string;

class FSDebug
{
public:
	static void Print(int message);
	static void Print(float message);
	static void Print(const string& message);
};

template<typename T> constexpr auto printFS(T message)
{
	return FSDebug::Print(message);
}
